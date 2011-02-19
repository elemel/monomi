#include "character_states.hpp"

#include "character_actor.hpp"

#include <Box2D/Dynamics/b2Fixture.h>

namespace monomi {
    // FALL ///////////////////////////////////////////////////////////////////

    void CharacterFallState::enter()
    { }

    void CharacterFallState::leave()
    { }

    StatePtr CharacterFallState::transition()
    {
        if (character_->testContact(DOWN_CONTACT_FLAG)) {
            return StatePtr(new CharacterStandState(character_));
        }
        if (character_->testContact(LEFT_CONTACT_FLAG) ||
            character_->testContact(RIGHT_CONTACT_FLAG))
        {
            return StatePtr(new CharacterWallSlideState(character_));
        }
        if (character_->testInput(DOWN_INPUT_FLAG)) {
            return StatePtr(new CharacterStompState(character_));
        }
        return StatePtr();
    }

    void CharacterFallState::update(float dt)
    {
        (void) dt;
    }

    void CharacterFallState::print(std::ostream &out) const
    {
        out << "fall";
    }

    // JUMP ///////////////////////////////////////////////////////////////////

    void CharacterJumpState::enter()
    {
        float jumpVelocity = character_->jumpVelocity();
        float horizontalVelocity = character_->horizontalVelocity();
        if (horizontalVelocity < jumpVelocity) {
            float verticalVelocity = std::sqrt(square(jumpVelocity) -
                                               square(horizontalVelocity));
            character_->verticalVelocity(verticalVelocity);
        }
    }

    void CharacterJumpState::leave()
    { }

    StatePtr CharacterJumpState::transition()
    {
        return StatePtr(new CharacterFallState(character_));
    }

    void CharacterJumpState::update(float dt)
    {
        (void) dt;
    }

    void CharacterJumpState::print(std::ostream &out) const
    {
        out << "jump";
    }

    // RUN ////////////////////////////////////////////////////////////////////

    void CharacterRunState::enter()
    { }

    void CharacterRunState::leave()
    { }

    StatePtr CharacterRunState::transition()
    {
        if (!character_->testContact(DOWN_CONTACT_FLAG)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->testInput(RUN_INPUT_FLAG)) {
            return StatePtr(new CharacterWalkState(character_));
        }
        if (character_->testInput(JUMP_INPUT_FLAG)) {
            return StatePtr(new CharacterJumpState(character_));
        }
        if (!character_->testInput(LEFT_INPUT_FLAG) &&
            !character_->testInput(RIGHT_INPUT_FLAG))
        {
            return StatePtr(new CharacterWalkState(character_));
        }
        if (character_->testContact(LEFT_CONTACT_FLAG) &&
            character_->testInput(LEFT_INPUT_FLAG) ||
            character_->testContact(RIGHT_CONTACT_FLAG) &&
            character_->testInput(RIGHT_INPUT_FLAG))
        {
            return StatePtr(new CharacterWallRunState(character_));
        }
        return StatePtr();
    }

    void CharacterRunState::update(float dt)
    {
        float velocity = character_->horizontalVelocity();
        int horizontalInput = (int(character_->testInput(RIGHT_INPUT_FLAG)) -
                               int(character_->testInput(LEFT_INPUT_FLAG)));
        velocity += (dt * character_->runAcceleration() *
                     float(horizontalInput));
        velocity = sign(velocity) * std::min(std::abs(velocity),
                                             character_->runVelocity());
        character_->horizontalVelocity(velocity);
    }

    void CharacterRunState::print(std::ostream &out) const
    {
        out << "run";
    }

    // STAND //////////////////////////////////////////////////////////////////

    void CharacterStandState::enter()
    {
        character_->fixture()->SetFriction(5.0f);
    }

    void CharacterStandState::leave()
    {
        character_->fixture()->SetFriction(0.0f);
    }

    StatePtr CharacterStandState::transition()
    {
        if (!character_->testContact(DOWN_CONTACT_FLAG)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->testInput(JUMP_INPUT_FLAG)) {
            return StatePtr(new CharacterJumpState(character_));
        }
        if (character_->testInput(LEFT_INPUT_FLAG) ||
            character_->testInput(RIGHT_INPUT_FLAG))
        {
            return StatePtr(new CharacterWalkState(character_));
        }
        return StatePtr();
    }

    void CharacterStandState::update(float dt)
    {
        (void) dt;
    }

    void CharacterStandState::print(std::ostream &out) const
    {
        out << "stand";
    }

    // STOMP //////////////////////////////////////////////////////////////////

    void CharacterStompState::enter()
    { }

    void CharacterStompState::leave()
    { }

    StatePtr CharacterStompState::transition()
    {
        if (character_->testContact(DOWN_CONTACT_FLAG)) {
            return StatePtr(new CharacterStandState(character_));
        }
        return StatePtr();
    }

    void CharacterStompState::update(float dt)
    {
        (void) dt;
    }

    void CharacterStompState::print(std::ostream &out) const
    {
        out << "stomp";
    }

    // WALK ///////////////////////////////////////////////////////////////////

    void CharacterWalkState::enter()
    { }

    void CharacterWalkState::leave()
    { }

    StatePtr CharacterWalkState::transition()
    {
        if (!character_->testContact(DOWN_CONTACT_FLAG)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->testInput(LEFT_INPUT_FLAG) &&
            !character_->testInput(RIGHT_INPUT_FLAG))
        {
            return StatePtr(new CharacterStandState(character_));
        }
        if (character_->testInput(RUN_INPUT_FLAG)) {
            return StatePtr(new CharacterRunState(character_));
        }
        if (character_->testInput(JUMP_INPUT_FLAG)) {
            return StatePtr(new CharacterJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWalkState::update(float dt)
    {
        float velocity = character_->horizontalVelocity();
        int horizontalInput = (int(character_->testInput(RIGHT_INPUT_FLAG)) -
                               int(character_->testInput(LEFT_INPUT_FLAG)));
        velocity += (dt * character_->walkAcceleration() *
                     float(horizontalInput));
        velocity = sign(velocity) * std::min(std::abs(velocity),
                                             character_->walkVelocity());
        character_->horizontalVelocity(velocity);
    }

    void CharacterWalkState::print(std::ostream &out) const
    {
        out << "walk";
    }

    // WALL JUMP //////////////////////////////////////////////////////////////

    void CharacterWallJumpState::enter()
    {
        int horizontalContact = (int(character_->testContact(RIGHT_CONTACT_FLAG)) -
                                 int(character_->testContact(LEFT_CONTACT_FLAG)));
        float wallJumpVelocity = character_->wallJumpVelocity();
        float wallJumpAngle = character_->wallJumpAngle();
        float horizontalVelocity = float(-horizontalContact) * std::cos(wallJumpAngle) * wallJumpVelocity;
        float verticalVelocity = std::sin(wallJumpAngle) * wallJumpVelocity;
        character_->horizontalVelocity(horizontalVelocity);
        character_->verticalVelocity(verticalVelocity);
    }

    void CharacterWallJumpState::leave()
    { }

    StatePtr CharacterWallJumpState::transition()
    {
        return StatePtr(new CharacterFallState(character_));
    }

    void CharacterWallJumpState::update(float dt)
    {
        (void) dt;
    }

    void CharacterWallJumpState::print(std::ostream &out) const
    {
        out << "wall-jump";
    }

    // WALL RUN ///////////////////////////////////////////////////////////////

    void CharacterWallRunState::enter()
    { }

    void CharacterWallRunState::leave()
    { }

    StatePtr CharacterWallRunState::transition()
    {
        if (!character_->testContact(LEFT_CONTACT_FLAG) &&
            !character_->testContact(RIGHT_CONTACT_FLAG))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->testContact(UP_CONTACT_FLAG)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->testInput(LEFT_INPUT_FLAG) &&
            !character_->testInput(RIGHT_INPUT_FLAG) &&
            !character_->testInput(UP_INPUT_FLAG))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->testInput(JUMP_INPUT_FLAG)) {
            return StatePtr(new CharacterWallJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWallRunState::update(float dt)
    {
        (void) dt;
        character_->verticalVelocity(character_->wallRunVelocity());
    }

    void CharacterWallRunState::print(std::ostream &out) const
    {
        out << "wall-run";
    }

    // WALL SLIDE /////////////////////////////////////////////////////////////

    void CharacterWallSlideState::enter()
    { }

    void CharacterWallSlideState::leave()
    { }

    StatePtr CharacterWallSlideState::transition()
    {
        if (!character_->testContact(LEFT_CONTACT_FLAG) &&
            !character_->testContact(RIGHT_CONTACT_FLAG))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->testInput(DOWN_INPUT_FLAG)) {
            return StatePtr(new CharacterStompState(character_));
        }
        if (character_->testInput(JUMP_INPUT_FLAG)) {
            return StatePtr(new CharacterWallJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWallSlideState::update(float dt)
    {
        (void) dt;

        float velocity = character_->verticalVelocity();
        velocity = sign(velocity) * std::min(std::abs(velocity),
                                             character_->wallSlideVelocity());
        character_->verticalVelocity(velocity);
    }

    void CharacterWallSlideState::print(std::ostream &out) const
    {
        out << "wall-slide";
    }
}
