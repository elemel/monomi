#include "character_states.hpp"

#include "character_actor.hpp"

namespace monomi {
    void CharacterFallState::enter()
    { }

    void CharacterFallState::leave()
    { }

    StatePtr CharacterFallState::transition()
    {
        if (character_->testSupport(DOWN_SUPPORT_FLAG)) {
            return StatePtr(new CharacterStandState(character_));
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

    void CharacterJumpState::enter()
    {
        character_->verticalVelocity(10.0f);
    }

    inline void CharacterJumpState::leave()
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

    inline void CharacterStandState::enter()
    { }

    inline void CharacterStandState::leave()
    { }

    StatePtr CharacterStandState::transition()
    {
        if (!character_->testSupport(DOWN_SUPPORT_FLAG)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->testControl(JUMP_CONTROL_FLAG)) {
            return StatePtr(new CharacterJumpState(character_));
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
}
