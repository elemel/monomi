#include "game.hpp"

#include "block_actor.hpp"
#include "character_actor.hpp"
#include "character_factory.hpp"
#include "character_type.hpp"
#include "random.hpp"

namespace monomi {
    namespace {
        boost::shared_ptr<BlockActor> createBlock(int x, int y)
        {
            boost::shared_ptr<BlockActor> block(new BlockActor);
            block->box.p1 = Point2(float(x), float(y));
            block->box.p2 = Point2(float(x + 1), float(y + 1));
            return block;
        }
    }

    Game::Game() :
        time_(0.0f),
        random_(new Random(std::time(0))),
        characterFactory_(new CharacterFactory)
    {
        // Create characters.
        characters_.push_back(characterFactory_->createEarthMaster());
        characters_.back()->position = Point2(2.0f, 2.0f);
        characters_.push_back(characterFactory_->createSamurai());
        characters_.back()->position = Point2(7.0f, 5.0f);
        characters_.push_back(characterFactory_->createSamurai());
        characters_.back()->position = Point2(9.0f, 5.0f);
        characters_.push_back(characterFactory_->createSamurai());
        characters_.back()->position = Point2(11.0f, 5.0f);

        // Create blocks.
        blocks_.push_back(createBlock(0, 0));
        blocks_.push_back(createBlock(0, 3));
        blocks_.push_back(createBlock(1, 0));
        blocks_.push_back(createBlock(2, 0));
        blocks_.push_back(createBlock(3, 0));
        blocks_.push_back(createBlock(3, 1));
        blocks_.push_back(createBlock(3, 2));
        blocks_.push_back(createBlock(3, 3));
        blocks_.push_back(createBlock(3, 4));
        blocks_.push_back(createBlock(3, 5));
        blocks_.push_back(createBlock(3, 6));
        blocks_.push_back(createBlock(4, 0));
        blocks_.push_back(createBlock(5, 0));
        blocks_.push_back(createBlock(6, 0));
        blocks_.push_back(createBlock(7, 0));
        blocks_.push_back(createBlock(7, 3));
        blocks_.push_back(createBlock(7, 4));
        blocks_.push_back(createBlock(7, 5));
        blocks_.push_back(createBlock(7, 6));
        blocks_.push_back(createBlock(7, 7));
        blocks_.push_back(createBlock(7, 8));
        blocks_.push_back(createBlock(8, 0));
        blocks_.push_back(createBlock(9, 0));
        blocks_.push_back(createBlock(10, 0));
        blocks_.push_back(createBlock(11, 0));
        blocks_.push_back(createBlock(12, 0));
        blocks_.push_back(createBlock(13, 0));
        blocks_.push_back(createBlock(14, 0));
        blocks_.push_back(createBlock(15, 0));
        blocks_.push_back(createBlock(16, 0));
        blocks_.push_back(createBlock(17, 0));
        blocks_.push_back(createBlock(18, 0));
    }

    void Game::update(float dt)
    {
        typedef std::vector<boost::shared_ptr<CharacterActor> >::iterator Iterator;
        for (Iterator i = characters_.begin(); i != characters_.end(); ++i)
        {
            (*i)->update(dt);
        }
        resolveCollisions();
    }

    void Game::resolveCollisions()
    {
        resolveBlockCollisions();
        resolveCharacterCollisions();
    }

    void Game::resolveBlockCollisions()
    {
        typedef std::vector<boost::shared_ptr<CharacterActor> >::iterator CharacterIterator;
        for (CharacterIterator i = characters_.begin(); i != characters_.end();
             ++i)
        {
            if ((*i)->alive) {
                // Resolve collisions. Make multiple iterations, resolving only
                // the deepest collision found during each iteration.
                for (int j = 0; j < 3; ++j) {
                    // Find the deepest collision.
                    float maxSquaredLength = -1.0f;
                    LineSegment2 maxSeparator;
                    typedef std::vector<boost::shared_ptr<BlockActor> >::iterator BlockIterator;
                    for (BlockIterator k = blocks_.begin(); k != blocks_.end();
                         ++k)
                    {
                        if (intersects((*i)->bottomCircle(), (*k)->box)) {
                            LineSegment2 separator =
                                separate((*i)->bottomCircle(), (*k)->box);
                            if (separator.squaredLength() >= maxSquaredLength)
                            {
                                maxSquaredLength = separator.squaredLength();
                                maxSeparator = separator;
                            }
                        }
                        if (intersects((*i)->topCircle(), (*k)->box)) {
                            LineSegment2 separator =
                                separate((*i)->topCircle(), (*k)->box);
                            if (separator.squaredLength() >= maxSquaredLength)
                            {
                                maxSquaredLength = separator.squaredLength();
                                maxSeparator = separator;
                            }
                        }
                    }

                    // Resolve the deepest collision.
                    if (maxSquaredLength >= 0.0f) {
                        // Separate the colliding shapes, and cancel any
                        // negative velocity along the collision normal.
                        Vector2 normal = maxSeparator.p2 - maxSeparator.p1;
                        (*i)->position += normal;
                        normal.normalize();
                        (*i)->velocity -= (normal *
                                           std::min(dot((*i)->velocity, normal),
                                                    0.0f));
                    }
                }
            }
            updateTouchFlags(i->get());
        }
    }

    void Game::updateTouchFlags(CharacterActor *character)
    {
        // Clear touch flags.
        character->touchLeft = false;
        character->touchRight = false;
        character->touchDown = false;
        character->touchUp = false;

        // Set touch flags.
        for (int i = 0; i < 2; ++i) {
            Circle circle = i ? character->bottomCircle() :
                                character->topCircle();
            circle.radius += 0.02f;
            typedef std::vector<boost::shared_ptr<BlockActor> >::iterator Iterator;
            for (Iterator j = blocks_.begin(); j != blocks_.end(); ++j) {
                if (intersects(circle, (*j)->box)) {
                    LineSegment2 separator = separate(circle, (*j)->box);
                    Vector2 normal = separator.p2 - separator.p1;
                    normal.normalize();
                    float velocity = dot(character->velocity, normal);
                    if (std::abs(velocity) <= 0.02f) {
                        if (normal.x >= 0.98f) {
                            character->touchLeft = true;
                        }
                        if (normal.x <= -0.98f) {
                            character->touchRight = true;
                        }
                        if (normal.y >= 0.98f) {
                            character->touchDown = true;
                        }
                        if (normal.y <= -0.98f) {
                            character->touchUp = true;
                        }
                    }
                }
            }
        }
    }

    void Game::resolveCharacterCollisions()
    {
        boost::shared_ptr<CharacterActor> playerCharacter = characters_.front();
        typedef std::vector<boost::shared_ptr<CharacterActor> >::iterator Iterator;
        for (Iterator i = characters_.begin() + 1; i != characters_.end(); ++i)
        {
            if (playerCharacter->alive && (*i)->alive &&
                (intersects(playerCharacter->bottomCircle(),
                            (*i)->bottomCircle()) ||
                 intersects(playerCharacter->bottomCircle(),
                            (*i)->topCircle()) ||
                 intersects(playerCharacter->topCircle(),
                            (*i)->bottomCircle()) ||
                 intersects(playerCharacter->topCircle(),
                            (*i)->topCircle())))
            {
                int side = int(sign((*i)->position.x -
                                    playerCharacter->position.x));
                if (side == (*i)->face) {
                    (*i)->alive = false;
                } else {
                    playerCharacter->alive = false;
                }
                playerCharacter->velocity *= 0.5f;
                (*i)->velocity *= 0.5f;
            }
        }
    }
}
