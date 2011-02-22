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
        if (character_->sensorFlags().test(CharacterActor::FLOOR_SENSOR)) {
            return StatePtr(new CharacterStandState(character_));
        }
        if (character_->sensorFlags().test(CharacterActor::LEFT_WALL_SENSOR) ||
            character_->sensorFlags().test(CharacterActor::RIGHT_WALL_SENSOR))
        {
            return StatePtr(new CharacterWallSlideState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::DOWN_CONTROL)) {
            return StatePtr(new CharacterStompState(character_));
        }
        return StatePtr();
    }

    void CharacterFallState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        velocity.y -= dt * character_->type()->fallAcceleration();
        velocity.clamp(character_->type()->fallVelocity());
        character_->velocity(velocity);
    }

    void CharacterFallState::print(std::ostream &out) const
    {
        out << "fall";
    }

    // JUMP ///////////////////////////////////////////////////////////////////

    void CharacterJumpState::enter()
    {
        Vector2 velocity = character_->velocity();
        float jumpVelocity = character_->type()->jumpVelocity();
        if (velocity.x < jumpVelocity) {
            velocity.y = std::sqrt(square(jumpVelocity) - square(velocity.x));
            character_->velocity(velocity);
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
        if (!character_->sensorFlags().test(CharacterActor::FLOOR_SENSOR)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->controlFlags().test(CharacterActor::RUN_CONTROL)) {
            return StatePtr(new CharacterWalkState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::JUMP_CONTROL)) {
            return StatePtr(new CharacterJumpState(character_));
        }
        if (!character_->controlFlags().test(CharacterActor::LEFT_CONTROL) &&
            !character_->controlFlags().test(CharacterActor::RIGHT_CONTROL))
        {
            return StatePtr(new CharacterWalkState(character_));
        }
        if (character_->sensorFlags().test(CharacterActor::LEFT_WALL_SENSOR) &&
            character_->controlFlags().test(CharacterActor::LEFT_CONTROL) ||
            character_->sensorFlags().test(CharacterActor::RIGHT_WALL_SENSOR) &&
            character_->controlFlags().test(CharacterActor::RIGHT_CONTROL))
        {
            return StatePtr(new CharacterWallRunState(character_));
        }
        return StatePtr();
    }

    void CharacterRunState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalControl = (float(character_->controlFlags().test(CharacterActor::RIGHT_CONTROL)) -
                                 float(character_->controlFlags().test(CharacterActor::LEFT_CONTROL)));
        velocity.x += (dt * character_->type()->runAcceleration() * horizontalControl);
        velocity.x = sign(velocity.x) * std::min(std::abs(velocity.x),
                                                 character_->type()->runVelocity());
        velocity.y -= dt * character_->type()->fallAcceleration();
        character_->velocity(velocity);
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
        if (!character_->sensorFlags().test(CharacterActor::FLOOR_SENSOR)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::JUMP_CONTROL)) {
            return StatePtr(new CharacterJumpState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::LEFT_CONTROL) ||
            character_->controlFlags().test(CharacterActor::RIGHT_CONTROL))
        {
            return StatePtr(new CharacterWalkState(character_));
        }
        return StatePtr();
    }

    void CharacterStandState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        velocity.y -= dt * character_->type()->fallAcceleration();
        character_->velocity(velocity);
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
        if (character_->sensorFlags().test(CharacterActor::FLOOR_SENSOR)) {
            return StatePtr(new CharacterStandState(character_));
        }
        return StatePtr();
    }

    void CharacterStompState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        velocity.y -= dt * character_->type()->stompAcceleration();
        velocity.clamp(character_->type()->stompVelocity());
        character_->velocity(velocity);
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
        if (!character_->sensorFlags().test(CharacterActor::FLOOR_SENSOR)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->controlFlags().test(CharacterActor::LEFT_CONTROL) &&
            !character_->controlFlags().test(CharacterActor::RIGHT_CONTROL))
        {
            return StatePtr(new CharacterStandState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::RUN_CONTROL)) {
            return StatePtr(new CharacterRunState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::JUMP_CONTROL)) {
            return StatePtr(new CharacterJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWalkState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalControl = (float(character_->controlFlags().test(CharacterActor::RIGHT_CONTROL)) -
                                  float(character_->controlFlags().test(CharacterActor::LEFT_CONTROL)));
        velocity.x += dt * character_->type()->walkAcceleration() * horizontalControl;
        velocity.x = sign(velocity.x) * std::min(std::abs(velocity.x),
                                                 character_->type()->walkVelocity());
        velocity.y -= dt * character_->type()->fallAcceleration();
        character_->velocity(velocity);
    }

    void CharacterWalkState::print(std::ostream &out) const
    {
        out << "walk";
    }

    // WALL JUMP //////////////////////////////////////////////////////////////

    void CharacterWallJumpState::enter()
    {
        Vector2 velocity = character_->velocity();
        float horizontalContact = (float(character_->sensorFlags().test(CharacterActor::RIGHT_WALL_SENSOR)) -
                                   float(character_->sensorFlags().test(CharacterActor::LEFT_WALL_SENSOR)));
        float wallJumpVelocity = character_->type()->wallJumpVelocity();
        float wallJumpAngle = character_->type()->wallJumpAngle();
        velocity.x = -horizontalContact * std::cos(wallJumpAngle) * wallJumpVelocity;
        velocity.y = std::sin(wallJumpAngle) * wallJumpVelocity;
        character_->velocity(velocity);
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
        if (!character_->sensorFlags().test(CharacterActor::LEFT_WALL_SENSOR) &&
            !character_->sensorFlags().test(CharacterActor::RIGHT_WALL_SENSOR))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->sensorFlags().test(CharacterActor::CEILING_SENSOR)) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->controlFlags().test(CharacterActor::LEFT_CONTROL) &&
            !character_->controlFlags().test(CharacterActor::RIGHT_CONTROL) &&
            !character_->controlFlags().test(CharacterActor::UP_CONTROL))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::JUMP_CONTROL)) {
            return StatePtr(new CharacterWallJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWallRunState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalContact = (float(character_->sensorFlags().test(CharacterActor::RIGHT_WALL_SENSOR)) -
                                   float(character_->sensorFlags().test(CharacterActor::LEFT_WALL_SENSOR)));
        velocity.x += dt * horizontalContact * character_->type()->fallAcceleration();
        velocity.y += dt * character_->type()->wallRunAcceleration();
        velocity.clamp(character_->type()->wallRunVelocity());
        character_->velocity(velocity);
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
        if (!character_->sensorFlags().test(CharacterActor::LEFT_WALL_SENSOR) &&
            !character_->sensorFlags().test(CharacterActor::RIGHT_WALL_SENSOR))
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->sensorFlags().test(CharacterActor::FLOOR_SENSOR)) {
            return StatePtr(new CharacterStandState(character_));
        }
        if (character_->controlFlags().test(CharacterActor::JUMP_CONTROL)) {
            return StatePtr(new CharacterWallJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWallSlideState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalContact = (float(character_->sensorFlags().test(CharacterActor::RIGHT_WALL_SENSOR)) -
                                   float(character_->sensorFlags().test(CharacterActor::LEFT_WALL_SENSOR)));
        velocity.x += dt * horizontalContact * character_->type()->fallAcceleration();
        velocity.y -= dt * character_->type()->wallSlideAcceleration();
        velocity.clamp(character_->type()->wallSlideVelocity());
        character_->velocity(velocity);
    }

    void CharacterWallSlideState::print(std::ostream &out) const
    {
        out << "wall-slide";
    }
}
