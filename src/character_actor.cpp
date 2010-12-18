#include "character_actor.hpp"

#include "character_type.hpp"
#include "debug_graphics.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterActor::CharacterActor(boost::shared_ptr<CharacterType const> const &type) :
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

    bool CharacterActor::wallSliding() const
    {
        return (techniques.test(wallSlideTechnique) &&
                tools.test(tigerClawTool) && (touchLeft || touchRight));
    }

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

    void CharacterActor::update(float dt)
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

    void CharacterActor::debugDraw(DebugGraphics *debugGraphics)
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
        debugGraphics->drawCircle(bottomCircle(), color);
        debugGraphics->drawCircle(topCircle(), color);
        Circle c = topCircle();
        LineSegment2 s(c.center,
                       c.center + Vector2(float(face) * c.radius, 0.0f));
        debugGraphics->drawLineSegment(s, color);
    }
}
