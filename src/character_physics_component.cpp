#include "character_physics_component.hpp"

#include "block_actor.hpp"
#include "character_actor.hpp"
#include "character_type.hpp"
#include "game.hpp"

#include <cmath>
#include <iostream>
#include <vector>

namespace monomi {
    CharacterPhysicsComponent::CharacterPhysicsComponent(CharacterActor *character, Game *game) :
        character_(character),
        game_(game)
    { }

    void CharacterPhysicsComponent::update(float dt)
    {
        // Physics simulation.
        character_->velocity += dt * character_->gravity;
        if (character_->velocity.squaredLength() >= character_->type->maxVelocity * character_->type->maxVelocity)
        {
            character_->velocity.normalize();
            character_->velocity *= character_->type->maxVelocity;
        }
        character_->position += dt * character_->velocity;

        // Apply constraints.
        if (character_->alive_) {
            // Make multiple iterations, separating only the deepest
            // penetration found during each iteration.
            for (int j = 0; j < 3; ++j) {
                // Find the deepest penetration.
                float maxSquaredLength = -1.0f;
                LineSegment2 maxSeparator;
                typedef std::vector<boost::shared_ptr<Actor> >::iterator ActorIterator;
                for (ActorIterator k = game_->actors_.begin();
                     k != game_->actors_.end(); ++k)
                {
                    if (boost::shared_ptr<BlockActor> block =
                        boost::dynamic_pointer_cast<BlockActor>(*k))
                    {
                        if (intersects(character_->bottomCircle(), block->box)) {
                            LineSegment2 separator =
                                separate(character_->bottomCircle(), block->box);
                            if (separator.squaredLength() >= maxSquaredLength)
                            {
                                maxSquaredLength = separator.squaredLength();
                                maxSeparator = separator;
                            }
                        }
                        if (intersects(character_->topCircle(), block->box)) {
                            LineSegment2 separator =
                                separate(character_->topCircle(), block->box);
                            if (separator.squaredLength() >= maxSquaredLength)
                            {
                                maxSquaredLength = separator.squaredLength();
                                maxSeparator = separator;
                            }
                        }
                    }
                }

                // Resolve the deepest penetration.
                if (maxSquaredLength >= 0.0f) {
                    // Separate the penetrating shapes, and cancel any
                    // negative velocity along the penetration normal.
                    Vector2 normal = maxSeparator.p2 - maxSeparator.p1;
                    character_->position += normal;
                    normal.normalize();
                    character_->velocity -= (normal *
                                             std::min(dot(character_->velocity, normal),
                                                      0.0f));
                }
            }
        }

        // Clear touch flags.
        character_->touchLeft = false;
        character_->touchRight = false;
        character_->touchDown = false;
        character_->touchUp = false;

        // Set touch flags.
        for (int j = 0; j < 2; ++j) {
            Circle circle = j ? character_->bottomCircle() :
                                character_->topCircle();
            circle.radius += 0.02f;
            typedef std::vector<boost::shared_ptr<Actor> >::iterator ActorIterator;
            for (ActorIterator k = game_->actors_.begin();
                 k != game_->actors_.end(); ++k)
            {
                if (boost::shared_ptr<BlockActor> block =
                    boost::dynamic_pointer_cast<BlockActor>(*k))
                {
                    if (intersects(circle, block->box)) {
                        LineSegment2 separator = separate(circle, block->box);
                        Vector2 normal = separator.p2 - separator.p1;
                        normal.normalize();
                        float velocity = dot(character_->velocity, normal);
                        if (std::abs(velocity) <= 0.02f) {
                            if (normal.x >= 0.98f) {
                                character_->touchLeft = true;
                            }
                            if (normal.x <= -0.98f) {
                                character_->touchRight = true;
                            }
                            if (normal.y >= 0.98f) {
                                character_->touchDown = true;
                            }
                            if (normal.y <= -0.98f) {
                                character_->touchUp = true;
                            }
                        }
                    }
                }
            }
        }
    }
}
