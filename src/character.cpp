#include "character.hpp"

#include "debug_graphics.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterType::CharacterType() :
        radius(0.75f),
        maxVelocity(20.0f),
        walkAcceleration(12.0f),
        maxWalkVelocity(8.0f),
        driftAcceleration(10.0f),
        maxDriftVelocity(6.0f),
        jumpVelocity(12.0f),
        wallJumpVelocity(6.0f, 9.0f),
        airJumpVelocity(12.0f)
    { }

    Character::Character(CharacterType const *type) :
        type(type),
        techniques(type->techniques),
        tools(type->tools),
        alive(true),
        face(1),
        gravity(0.0f, -20.0f),
        touchLeft(false),
        touchRight(false),
        touchDown(false),
        touchUp(false),
        airJumpCount(0)
    { }

    bool Character::wallSliding() const
    {
        return (techniques.test(wallSlideTechnique) &&
                tools.test(tigerClawTool) && (touchLeft || touchRight));
    }

    void Character::step(float dt)
    {
        if (touchDown) {
            if (techniques.test(tripleJumpTechnique)) {
                airJumpCount = 2;
            } else if (techniques.test(doubleJumpTechnique)) {
                airJumpCount = 1;
            } else {
                airJumpCount = 0;
            }
        } else if (wallSliding()) {
            airJumpCount = 0;
        }
        if (controls.test(jumpControl) && !oldControls.test(jumpControl)) {
            if (touchDown) {
                velocity.y = type->jumpVelocity;
            } else if (wallSliding()) {
                if (techniques.test(wallJumpTechnique)) {
                    int jumpFace = int(touchLeft) - int(touchRight);
                    if (jumpFace) {
                        face = jumpFace;
                    }
                    velocity.x = float(jumpFace) * type->wallJumpVelocity.x;
                    velocity.y = type->wallJumpVelocity.y;
                }
            } else {
                if (tools.test(ironFanTool) && airJumpCount) {
                    --airJumpCount;
                    velocity.y = type->airJumpVelocity;
                }
            }
        }
        int moveFace = (int(controls.test(rightControl)) -
                        int(controls.test(leftControl)));
        if (moveFace) {
            face = moveFace;
        }
        if (touchDown) {
            if (moveFace) {
                velocity.x += (float(moveFace) * type->walkAcceleration * dt);
                velocity.x = (sign(velocity.x) *
                              std::min(std::abs(velocity.x),
                                       type->maxWalkVelocity));
            } else {
                velocity.x = (sign(velocity.x) *
                              std::max(std::abs(velocity.x) -
                                       type->walkAcceleration * dt, 0.0f));
            }
        } else {
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
        if (!controls.test(jumpControl)) {
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
            if (touchDown) {
                color = debugColors::yellow();
            } else if (wallSliding()) {
                color = debugColors::red();
            } else {
                color = debugColors::lightBlue();
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
