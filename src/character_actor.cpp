#include "character_actor.hpp"

#include "block_actor.hpp"
#include "character_type.hpp"
#include "debug_graphics.hpp"
#include "game.hpp"
#include "state.hpp"
#include "state_machine.hpp"
#include "type.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterActor::CharacterActor(Game *game, CharacterType const *type) :
        game_(game),
        type_(type),
        techniques_(type->techniques),
        tools_(type->tools),
        alive_(true),
        face(1),
        gravity(0.0f, -20.0f),
        airJumpCount(0)
    { }

    CharacterType const *CharacterActor::type() const
    {
        return type_;
    }

    bool CharacterActor::testTechnique(Technique technique) const
    {
        return techniques_.test(technique);
    }

    void CharacterActor::setTechnique(Technique technique, bool value)
    {
        techniques_.set(technique, value);
    }

    bool CharacterActor::testTool(Tool tool) const
    {
        return tools_.test(tool);
    }

    void CharacterActor::setTool(Tool tool, bool value)
    {
        tools_.set(tool, value);
    }

    bool CharacterActor::testContact(Contact contact) const
    {
        return contacts_.test(contact);
    }

    void CharacterActor::setContact(Contact contact, bool value)
    {
        contacts_.set(contact, value);
    }

    bool CharacterActor::testInput(Input input) const
    {
        return inputs_.test(input);
    }

    void CharacterActor::setInput(Input input, bool value)
    {
        if (value != inputs_.test(input)) {
            inputs_.set(input, value);
            inputSignal_();
        }
    }

    Circle CharacterActor::bottomCircle() const
    {
        return Circle(position -
                      Vector2(0.0f, 0.5f * (type_->height - type_->width)),
                      0.5f * type_->width);
    }

    Circle CharacterActor::topCircle() const
    {
        return Circle(position +
                      Vector2(0.0f, 0.5f * (type_->height - type_->width)),
                      0.5f * type_->width);
    }

    Priority CharacterActor::priority() const
    {
        return dynamicPriority;
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
    }

    void CharacterActor::handleCollisions()
    {
        boost::shared_ptr<CharacterActor> playerCharacter =
            boost::dynamic_pointer_cast<CharacterActor>(game_->actors().front());
        if (playerCharacter.get() == this) {
            typedef std::vector<boost::shared_ptr<Actor> >::iterator
                ActorIterator;
            for (ActorIterator i = game_->actors().begin() + 1;
                 i != game_->actors().end(); ++i)
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

    void CharacterActor::debugDraw(DebugGraphicsPtr const &debugGraphics) const
    {
        DebugColor color = debugColors::white();
        if (alive_) {
            if (contacts_.test(downContact)) {
                color = debugColors::yellow();
            } else if (contacts_.test(leftContact) ||
                       contacts_.test(rightContact))
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

    boost::signals2::connection
    CharacterActor::connectContactSlot(ContactSlot const &slot)
    {
        return contactSignal_.connect(slot);
    }

    boost::signals2::connection
    CharacterActor::connectInputSlot(InputSlot const &slot)
    {
        return inputSignal_.connect(slot);
    }

    boost::signals2::connection
    CharacterActor::connectStateTransitionSlot(StateTransitionSlot const &slot)
    {
        return stateMachine_->connectTransitionSlot(slot);
    }

    void CharacterActor::updatePhysics(float dt)
    {
        velocity += dt * gravity;
        if (velocity.squaredLength() >=
            type_->maxVelocity * type_->maxVelocity)
        {
            velocity.normalize();
            velocity *= type_->maxVelocity;
        }
        position += dt * velocity;
    }

    void CharacterActor::applyConstraints()
    {
        if (alive_) {
            // Make multiple iterations, separating only the deepest
            // penetration found during each iteration.
            for (int j = 0; j < 3; ++j) {
                // Find the deepest penetration.
                float maxSquaredLength = -1.0f;
                LineSegment2 maxSeparator;
                typedef std::vector<boost::shared_ptr<Actor> >::iterator ActorIterator;
                for (ActorIterator k = game_->actors().begin();
                     k != game_->actors().end(); ++k)
                {
                    if (boost::shared_ptr<BlockActor> block =
                        boost::dynamic_pointer_cast<BlockActor>(*k))
                    {
                        if (intersects(bottomCircle(), block->box)) {
                            LineSegment2 separator =
                                separate(bottomCircle(), block->box);
                            if (separator.squaredLength() >= maxSquaredLength)
                            {
                                maxSquaredLength = separator.squaredLength();
                                maxSeparator = separator;
                            }
                        }
                        if (intersects(topCircle(), block->box)) {
                            LineSegment2 separator =
                                separate(topCircle(), block->box);
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
                    position += normal;
                    normal.normalize();
                    velocity -= (normal *
                                 std::min(dot(velocity, normal), 0.0f));
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
            for (ActorIterator k = game_->actors().begin();
                 k != game_->actors().end(); ++k)
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
        if (newContacts != contacts_) {
            contacts_ = newContacts;
            std::cout << "CharacterActor #" << this << " changes contacts to "
                      << contacts_ << std::endl;
            contactSignal_();
        }
    }

    void CharacterActor::onTransition()
    {
        std::cout << "CharacterActor #" << this << " changes state to "
                  << Type(typeid(*stateMachine_->state())) << std::endl;
    }
}
