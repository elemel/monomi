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
        typedef std::vector<boost::shared_ptr<Actor> >::iterator Iterator;
        for (Iterator i = game_->actors_.begin(); i != game_->actors_.end();
             ++i)
        {
            (*i)->update(dt);
        }
        applyConstraints();
        updateTouchFlags();
        resolveCollisions();
    }

    void Physics::applyConstraints()
    {
        typedef std::vector<boost::shared_ptr<Actor> >::iterator Iterator;
        for (Iterator i = game_->actors_.begin(); i != game_->actors_.end();
             ++i)
        {
            if (boost::shared_ptr<CharacterActor> character =
                boost::dynamic_pointer_cast<CharacterActor>(*i))
            {
                if (character->alive) {
                    // Resolve collisions. Make multiple iterations, resolving only
                    // the deepest collision found during each iteration.
                    for (int j = 0; j < 3; ++j) {
                        // Find the deepest collision.
                        float maxSquaredLength = -1.0f;
                        LineSegment2 maxSeparator;
                        for (Iterator k = game_->actors_.begin();
                             k != game_->actors_.end(); ++k)
                        {
                            if (boost::shared_ptr<BlockActor> block =
                                boost::dynamic_pointer_cast<BlockActor>(*k))
                            {
                                if (intersects(character->bottomCircle(), block->box)) {
                                    LineSegment2 separator =
                                        separate(character->bottomCircle(), block->box);
                                    if (separator.squaredLength() >= maxSquaredLength)
                                    {
                                        maxSquaredLength = separator.squaredLength();
                                        maxSeparator = separator;
                                    }
                                }
                                if (intersects(character->topCircle(), block->box)) {
                                    LineSegment2 separator =
                                        separate(character->topCircle(), block->box);
                                    if (separator.squaredLength() >= maxSquaredLength)
                                    {
                                        maxSquaredLength = separator.squaredLength();
                                        maxSeparator = separator;
                                    }
                                }
                            }
                        }

                        // Resolve the deepest collision.
                        if (maxSquaredLength >= 0.0f) {
                            // Separate the colliding shapes, and cancel any
                            // negative velocity along the collision normal.
                            Vector2 normal = maxSeparator.p2 - maxSeparator.p1;
                            character->position += normal;
                            normal.normalize();
                            character->velocity -= (normal *
                                                    std::min(dot(character->velocity, normal),
                                                             0.0f));
                        }
                    }
                }
            }
        }
    }

    void Physics::updateTouchFlags()
    {
        typedef std::vector<boost::shared_ptr<Actor> >::iterator Iterator;
        for (Iterator i = game_->actors_.begin(); i != game_->actors_.end();
             ++i)
        {
            if (boost::shared_ptr<CharacterActor> character =
                boost::dynamic_pointer_cast<CharacterActor>(*i))
            {
                // Clear touch flags.
                character->touchLeft = false;
                character->touchRight = false;
                character->touchDown = false;
                character->touchUp = false;

                // Set touch flags.
                for (int j = 0; j < 2; ++j) {
                    Circle circle = j ? character->bottomCircle() :
                                        character->topCircle();
                    circle.radius += 0.02f;
                    for (Iterator k = game_->actors_.begin();
                         k != game_->actors_.end(); ++k)
                    {
                        if (boost::shared_ptr<BlockActor> block =
                            boost::dynamic_pointer_cast<BlockActor>(*k))
                        {
                            if (intersects(circle, block->box)) {
                                LineSegment2 separator = separate(circle, block->box);
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
            }
        }
    }

    void Physics::resolveCollisions()
    {
        boost::shared_ptr<CharacterActor> playerCharacter = boost::dynamic_pointer_cast<CharacterActor>(game_->actors_.front());
        typedef std::vector<boost::shared_ptr<Actor> >::iterator Iterator;
        for (Iterator i = game_->actors_.begin() + 1;
             i != game_->actors_.end(); ++i)
        {
            if (boost::shared_ptr<CharacterActor> otherCharacter = boost::dynamic_pointer_cast<CharacterActor>(*i)) {
                if (playerCharacter->alive && otherCharacter->alive &&
                    (intersects(playerCharacter->bottomCircle(),
                                otherCharacter->bottomCircle()) ||
                     intersects(playerCharacter->bottomCircle(),
                                otherCharacter->topCircle()) ||
                     intersects(playerCharacter->topCircle(),
                                otherCharacter->bottomCircle()) ||
                     intersects(playerCharacter->topCircle(),
                                otherCharacter->topCircle())))
                {
                    int side = int(sign(otherCharacter->position.x -
                                        playerCharacter->position.x));
                    if (side == otherCharacter->face) {
                        otherCharacter->alive = false;
                    } else {
                        playerCharacter->alive = false;
                    }
                    playerCharacter->velocity *= 0.5f;
                    otherCharacter->velocity *= 0.5f;
                }
            }
        }
    }
}
