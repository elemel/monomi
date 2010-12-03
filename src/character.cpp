#include "character.hpp"

#include "debug_graphics.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterType::CharacterType() :
        key(0),
        radius(0.75f),
        maxVelocity(20.0f),
        walkAcceleration(12.0f),
        maxWalkVelocity(8.0f),
        driftAcceleration(10.0f),
        maxDriftVelocity(6.0f),
        jumpVelocity(12.0f),
        wallJumpVelocity(6.0f, 9.0f),
        airJumpVelocity(12.0f),
        maxAirJumpCount(1)
    { }

    CharacterControls::CharacterControls() :
        left(false),
        right(false),
        up(false),
        down(false),
        jump(false),
        action(false)
    { }

    Character::Character(CharacterType const *type) :
        type(type),
        alive(true),
        face(1),
        gravity(0.0f, -20.0f),
        state(characterStates::jumping),
        touchingLeftWall(false),
        touchingRightWall(false),
        touchingCeiling(false),
        touchingFloor(false),
        airJumpCount(0)
    { }

    void Character::step(float dt)
    {
        if (state == characterStates::walking) {
            airJumpCount = type->maxAirJumpCount;
        } else if (state == characterStates::wallSliding) {
            airJumpCount = 0;
        }
        if (controls.jump && !oldControls.jump) {
            if (state == characterStates::walking) {
                state = characterStates::jumping;
                velocity.y = type->jumpVelocity;
            } else if (state == characterStates::wallSliding) {
                state = characterStates::jumping;
                int jumpFace = int(touchingLeftWall) - int(touchingRightWall);
                if (jumpFace) {
                    face = jumpFace;
                }
                velocity.x = float(jumpFace) * type->wallJumpVelocity.x;
                velocity.y = type->wallJumpVelocity.y;
            } else if (state == characterStates::jumping) {
                if (airJumpCount) {
                    --airJumpCount;
                    velocity.y = type->airJumpVelocity;
                }
            }
        }
        int moveFace = int(controls.right) - int(controls.left);
        if (moveFace) {
            face = moveFace;
        }
        if (state == characterStates::walking) {
            if (moveFace) {
                velocity.x += (float(moveFace) * type->walkAcceleration *
                               dt);
                velocity.x = (sign(velocity.x) *
                              std::min(std::abs(velocity.x),
                                       type->maxWalkVelocity));
            } else {
                velocity.x = (sign(velocity.x) *
                              std::max(std::abs(velocity.x) -
                                       type->walkAcceleration * dt, 0.0f));
            }
        } else if (state == characterStates::jumping ||
                   state == characterStates::wallSliding)
        {
            if (moveFace) {
                float driftVelocity = (velocity.x + float(moveFace) *
                                       type->driftAcceleration * dt);
                velocity.x = (sign(driftVelocity) *
                              std::min(std::abs(driftVelocity),
                                       std::max(std::abs(velocity.x),
                                                type->maxDriftVelocity)));
            }
        }
        velocity += dt * gravity;
        if (state == characterStates::jumping && !controls.jump) {
            velocity.y = std::min(velocity.y, 3.0f);
        }
        if (velocity.squaredLength() >= type->maxVelocity * type->maxVelocity)
        {
            velocity.normalize();
            velocity *= type->maxVelocity;
        }
        position += dt * velocity;
        oldControls = controls;
    }

    void Character::debugDraw(DebugGraphics *debugGraphics)
    {
        DebugColor color = debugColors::white();
        if (alive) {
            switch (state) {
            case characterStates::jumping:
                color = debugColors::lightBlue();
                break;

            case characterStates::walking:
                color = debugColors::yellow();
                break;

            case characterStates::wallSliding:
                color = debugColors::red();
                break;
            }
        }
        debugGraphics->drawCircle(Circle(position, type->radius), color);
        Point2 eyeCenter1 = (position + type->radius *
                             Vector2(0.1f * float(face), 0.3f));
        Point2 eyeCenter2 = (position + type->radius *
                             Vector2(0.4f * float(face), 0.3f));
        debugGraphics->drawCircle(Circle(eyeCenter1, 0.1f * type->radius),
                                  color);
        debugGraphics->drawCircle(Circle(eyeCenter2, 0.1f * type->radius),
                                  color);
    }
}
