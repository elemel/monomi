#include "physics.hpp"

#include "block_actor.hpp"
#include "character_actor.hpp"
#include "game.hpp"

#include <cmath>

namespace monomi {
    Physics::Physics(Game *game) :
        game_(game)
    { }

    void Physics::update(float dt)
    {
        typedef std::vector<boost::shared_ptr<CharacterActor> >::iterator Iterator;
        for (Iterator i = game_->characters_.begin();
             i != game_->characters_.end(); ++i)
        {
            (*i)->update(dt);
        }
        resolveCollisions();
    }

    void Physics::resolveCollisions()
    {
        resolveBlockCollisions();
        resolveCharacterCollisions();
    }

    void Physics::resolveBlockCollisions()
    {
        typedef std::vector<boost::shared_ptr<CharacterActor> >::iterator CharacterIterator;
        for (CharacterIterator i = game_->characters_.begin();
             i != game_->characters_.end(); ++i)
        {
            if ((*i)->alive) {
                // Resolve collisions. Make multiple iterations, resolving only
                // the deepest collision found during each iteration.
                for (int j = 0; j < 3; ++j) {
                    // Find the deepest collision.
                    float maxSquaredLength = -1.0f;
                    LineSegment2 maxSeparator;
                    typedef std::vector<boost::shared_ptr<BlockActor> >::iterator BlockIterator;
                    for (BlockIterator k = game_->blocks_.begin();
                         k != game_->blocks_.end(); ++k)
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

    void Physics::updateTouchFlags(CharacterActor *character)
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
            for (Iterator j = game_->blocks_.begin();
                 j != game_->blocks_.end(); ++j)
            {
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

    void Physics::resolveCharacterCollisions()
    {
        boost::shared_ptr<CharacterActor> playerCharacter = game_->characters_.front();
        typedef std::vector<boost::shared_ptr<CharacterActor> >::iterator Iterator;
        for (Iterator i = game_->characters_.begin() + 1;
             i != game_->characters_.end(); ++i)
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
