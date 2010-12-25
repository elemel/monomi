#include "character_actor.hpp"

#include "block_actor.hpp"
#include "character_type.hpp"
#include "debug_graphics.hpp"
#include "game.hpp"
#include "state_machine.hpp"
#include "type.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterActor::CharacterActor(Game *game, CharacterType const *type) :
        game(game),
        type(type),
        techniques(type->techniques),
        tools(type->tools),
        alive_(true),
        face(1),
        gravity(0.0f, -20.0f),
        airJumpCount(0)
    { }

    Circle CharacterActor::bottomCircle() const
    {
        return Circle(position -
                      Vector2(0.0f, 0.5f * (type->height - type->width)),
                      0.5f * type->width);
    }

    Circle CharacterActor::topCircle() const
    {
        return Circle(position +
                      Vector2(0.0f, 0.5f * (type->height - type->width)),
                      0.5f * type->width);
    }

    bool CharacterActor::alive() const
    {
        return true;
    }

    void CharacterActor::update(float dt)
    {
        if (stateMachine_) {
            stateMachine_->update(dt);
        }

        updatePhysics(dt);
        applyConstraints();
        updateContacts();

        // Copy inputs.
        oldInputs = inputs;
    }

    void CharacterActor::handleCollisions()
    {
        boost::shared_ptr<CharacterActor> playerCharacter =
            boost::dynamic_pointer_cast<CharacterActor>(game->actors_.front());
        if (playerCharacter.get() == this) {
            typedef std::vector<boost::shared_ptr<Actor> >::iterator
                ActorIterator;
            for (ActorIterator i = game->actors_.begin() + 1;
                 i != game->actors_.end(); ++i)
            {
                if (boost::shared_ptr<CharacterActor> otherCharacter =
                    boost::dynamic_pointer_cast<CharacterActor>(*i))
                {
                    if (playerCharacter->alive_ && otherCharacter->alive_ &&
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
                            otherCharacter->alive_ = false;
                        } else {
                            playerCharacter->alive_ = false;
                        }
                        playerCharacter->velocity *= 0.5f;
                        otherCharacter->velocity *= 0.5f;
                    }
                }
            }
        }
    }

    void CharacterActor::debugDraw(DebugGraphics *debugGraphics)
    {
        DebugColor color = debugColors::white();
        if (alive_) {
            if (contacts.test(downContact)) {
                color = debugColors::yellow();
            } else if (contacts.test(leftContact) ||
                       contacts.test(rightContact))
            {
                color = debugColors::red();
            } else {
                color = debugColors::lightBlue();
            }
        }
        debugGraphics->drawCircle(bottomCircle(), color);
        debugGraphics->drawCircle(topCircle(), color);
        Circle c = topCircle();
        LineSegment2 s(c.center,
                       c.center + Vector2(float(face) * c.radius, 0.0f));
        debugGraphics->drawLineSegment(s, color);
    }

    void CharacterActor::updatePhysics(float dt)
    {
        CharacterActor *character_ = this;
        character_->velocity += dt * character_->gravity;
        if (character_->velocity.squaredLength() >= character_->type->maxVelocity * character_->type->maxVelocity)
        {
            character_->velocity.normalize();
            character_->velocity *= character_->type->maxVelocity;
        }
        character_->position += dt * character_->velocity;
    }

    void CharacterActor::applyConstraints()
    {
        CharacterActor *character_ = this;
        if (character_->alive_) {
            // Make multiple iterations, separating only the deepest
            // penetration found during each iteration.
            for (int j = 0; j < 3; ++j) {
                // Find the deepest penetration.
                float maxSquaredLength = -1.0f;
                LineSegment2 maxSeparator;
                typedef std::vector<boost::shared_ptr<Actor> >::iterator ActorIterator;
                for (ActorIterator k = game->actors_.begin();
                     k != game->actors_.end(); ++k)
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
    }

    void CharacterActor::updateContacts()
    {
        // Compute new contacts.
        ContactBits newContacts;
        for (int j = 0; j < 2; ++j) {
            Circle circle = j ? bottomCircle() : topCircle();
            circle.radius += 0.02f;
            typedef std::vector<boost::shared_ptr<Actor> >::iterator ActorIterator;
            for (ActorIterator k = game->actors_.begin();
                 k != game->actors_.end(); ++k)
            {
                if (boost::shared_ptr<BlockActor> block =
                    boost::dynamic_pointer_cast<BlockActor>(*k))
                {
                    if (intersects(circle, block->box)) {
                        LineSegment2 separator = separate(circle, block->box);
                        Vector2 normal = separator.p2 - separator.p1;
                        normal.normalize();
                        float normalVelocity = dot(velocity, normal);
                        if (std::abs(normalVelocity) <= 0.02f) {
                            if (normal.x >= 0.98f) {
                                newContacts.set(leftContact);
                            }
                            if (normal.x <= -0.98f) {
                                newContacts.set(rightContact);
                            }
                            if (normal.y >= 0.98f) {
                                newContacts.set(downContact);
                            }
                            if (normal.y <= -0.98f) {
                                newContacts.set(upContact);
                            }
                        }
                    }
                }
            }
        }

        // Set new contacts.
        if (newContacts != contacts) {
            contacts = newContacts;
            std::cout << "CharacterActor #" << this << " changes contacts to " << contacts << std::endl;
            contactSignal_();
        }
    }

    void CharacterActor::onTransition()
    {
        std::cout << "CharacterActor #" << this << " changes state to " << Type(typeid(*stateMachine_->state())) << std::endl;
    }
}
