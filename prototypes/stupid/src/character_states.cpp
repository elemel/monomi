#include "character_states.hpp"

#include "character_actor.hpp"

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
        character_->verticalVelocity(10.0f);
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
        if (character_->testContact(LEFT_CONTACT_FLAG) ||
            character_->testContact(RIGHT_CONTACT_FLAG))
        {
            return StatePtr(new CharacterWallRunState(character_));
        }
        return StatePtr();
    }

    void CharacterRunState::update(float dt)
    {
        (void) dt;
    }

    void CharacterRunState::print(std::ostream &out) const
    {
        out << "run";
    }

    // STAND //////////////////////////////////////////////////////////////////

    void CharacterStandState::enter()
    { }

    void CharacterStandState::leave()
    { }

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
        character_->horizontalVelocity(0.0f);
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
        if (character_->testInput(RUN_INPUT_FLAG)) {
            return StatePtr(new CharacterRunState(character_));
        }
        if (character_->testInput(JUMP_INPUT_FLAG)) {
            return StatePtr(new CharacterJumpState(character_));
        }
        if (!character_->testInput(LEFT_INPUT_FLAG) &&
            !character_->testInput(RIGHT_INPUT_FLAG))
        {
            return StatePtr(new CharacterStandState(character_));
        }
        return StatePtr();
    }

    void CharacterWalkState::update(float dt)
    {
        (void) dt;
    }

    void CharacterWalkState::print(std::ostream &out) const
    {
        out << "walk";
    }

    // WALL RUN ///////////////////////////////////////////////////////////////

    void CharacterWallRunState::enter()
    { }

    void CharacterWallRunState::leave()
    { }

    StatePtr CharacterWallRunState::transition()
    {
        if (!character_->testInput(LEFT_INPUT_FLAG) &&
            !character_->testInput(RIGHT_INPUT_FLAG) &&
            !character_->testInput(UP_INPUT_FLAG))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->testContact(LEFT_CONTACT_FLAG) &&
            !character_->testContact(RIGHT_CONTACT_FLAG))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->testContact(UP_CONTACT_FLAG)) {
            return StatePtr(new CharacterFallState(character_));
        }
        return StatePtr();
    }

    void CharacterWallRunState::update(float dt)
    {
        (void) dt;
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
        if (character_->testInput(DOWN_INPUT_FLAG)) {
            return StatePtr(new CharacterStompState(character_));
        }
        if (!character_->testContact(LEFT_CONTACT_FLAG) &&
            !character_->testContact(RIGHT_CONTACT_FLAG))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        return StatePtr();
    }

    void CharacterWallSlideState::update(float dt)
    {
        (void) dt;
    }

    void CharacterWallSlideState::print(std::ostream &out) const
    {
        out << "wall-slide";
    }
}
