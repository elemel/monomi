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
        if (character_->floorSensorFlag()) {
            return StatePtr(new CharacterStandState(character_));
        }
        if ((character_->leftWallSensorFlag() ||
             character_->rightWallSensorFlag()) &&
             character_->wallSlideTechniqueFlag())
        {
            return StatePtr(new CharacterWallSlideState(character_));
        }
        if (character_->downControlFlag() && character_->stompTechniqueFlag())
        {
            return StatePtr(new CharacterStompState(character_));
        }
        return StatePtr();
    }

    void CharacterFallState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        velocity.y -= dt * character_->fallAcceleration();
        velocity.clamp(character_->fallVelocity());
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
        float jumpVelocity = character_->jumpVelocity();
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
        if (!character_->floorSensorFlag()) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->runControlFlag()) {
            return StatePtr(new CharacterWalkState(character_));
        }
        if (character_->jumpControlFlag()) {
            return StatePtr(new CharacterJumpState(character_));
        }
        if (!character_->leftControlFlag() && !character_->rightControlFlag())
        {
            return StatePtr(new CharacterWalkState(character_));
        }
        if ((character_->leftWallSensorFlag() &&
             character_->leftControlFlag() ||
             character_->rightWallSensorFlag() &&
             character_->rightControlFlag()) &&
            character_->wallRunTechniqueFlag())
        {
            return StatePtr(new CharacterWallRunState(character_));
        }
        return StatePtr();
    }

    void CharacterRunState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalControl = (float(character_->rightControlFlag()) -
                                   float(character_->leftControlFlag()));
        velocity.x += (dt * character_->runAcceleration() * horizontalControl);
        velocity.x = sign(velocity.x) * std::min(std::abs(velocity.x),
                                                 character_->runVelocity());
        velocity.y -= dt * character_->fallAcceleration();
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
        if (!character_->floorSensorFlag()) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->jumpControlFlag()) {
            return StatePtr(new CharacterJumpState(character_));
        }
        if (character_->leftControlFlag() ||
            character_->rightControlFlag())
        {
            return StatePtr(new CharacterWalkState(character_));
        }
        return StatePtr();
    }

    void CharacterStandState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        velocity.y -= dt * character_->fallAcceleration();
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
        if (character_->floorSensorFlag()) {
            return StatePtr(new CharacterStandState(character_));
        }
        return StatePtr();
    }

    void CharacterStompState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        velocity.y -= dt * character_->stompAcceleration();
        velocity.clamp(character_->stompVelocity());
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
        if (!character_->floorSensorFlag()) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->leftControlFlag() &&
            !character_->rightControlFlag())
        {
            return StatePtr(new CharacterStandState(character_));
        }
        if (character_->runControlFlag()) {
            return StatePtr(new CharacterRunState(character_));
        }
        if (character_->jumpControlFlag()) {
            return StatePtr(new CharacterJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWalkState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalControl = (float(character_->rightControlFlag()) -
                                   float(character_->leftControlFlag()));
        velocity.x += dt * character_->walkAcceleration() * horizontalControl;
        velocity.x = sign(velocity.x) * std::min(std::abs(velocity.x),
                                                 character_->walkVelocity());
        velocity.y -= dt * character_->fallAcceleration();
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
        float horizontalSensor = (float(character_->rightWallSensorFlag()) -
                                  float(character_->leftWallSensorFlag()));
        float wallJumpVelocity = character_->wallJumpVelocity();
        float wallJumpAngle = character_->wallJumpAngle();
        velocity.x = -horizontalSensor * std::cos(wallJumpAngle) * wallJumpVelocity;
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
        if (!character_->leftWallSensorFlag() &&
            !character_->rightWallSensorFlag())
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->ceilingSensorFlag()) {
            return StatePtr(new CharacterFallState(character_));
        }
        if (!character_->leftControlFlag() &&
            !character_->rightControlFlag() &&
            !character_->upControlFlag())
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->jumpControlFlag() &&
            character_->wallJumpTechniqueFlag())
        {
            return StatePtr(new CharacterWallJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWallRunState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalSensor = (float(character_->rightWallSensorFlag()) -
                                  float(character_->leftWallSensorFlag()));
        velocity.x += dt * horizontalSensor * character_->fallAcceleration();
        velocity.y += dt * character_->wallRunAcceleration();
        velocity.clamp(character_->wallRunVelocity());
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
        if (!character_->leftWallSensorFlag() &&
            !character_->rightWallSensorFlag())
        {
            return StatePtr(new CharacterFallState(character_));
        }
        if (character_->floorSensorFlag()) {
            return StatePtr(new CharacterStandState(character_));
        }
        if (character_->jumpControlFlag() &&
            character_->wallJumpTechniqueFlag())
        {
            return StatePtr(new CharacterWallJumpState(character_));
        }
        return StatePtr();
    }

    void CharacterWallSlideState::update(float dt)
    {
        Vector2 velocity = character_->velocity();
        float horizontalSensor = (float(character_->rightWallSensorFlag()) -
                                  float(character_->leftWallSensorFlag()));
        velocity.x += dt * horizontalSensor * character_->fallAcceleration();
        velocity.y -= dt * character_->wallSlideAcceleration();
        velocity.clamp(character_->wallSlideVelocity());
        character_->velocity(velocity);
    }

    void CharacterWallSlideState::print(std::ostream &out) const
    {
        out << "wall-slide";
    }
}
