#include "character.hpp"

#include "debug_graphics.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    Techniques::Techniques() :
        ambush(false),
        charge(false),
        dive(false),
        disguise(false),
        doubleJump(false),
        drop(false),
        ledgeGrab(false),
        ledgeJump(false),
        run(false),
        slam(false),
        slowFall(false),
        split(false),
        sprint(false),
        swim(false),
        teleport(false),
        tripleJump(false),
        wallJump(false),
        wallSlide(false)
    { }

    Equipment::Equipment() :
        airSkin(false),
        bambooFlute(false),
        grapplingHook(false),
        ironFan(false),
        smokeBombs(false),
        strawBasket(false),
        tigerClaws(false),
        throwingStars(false)
    { }

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

    CharacterControls::CharacterControls() :
        left(false),
        right(false),
        down(false),
        up(false),
        jump(false),
        action(false)
    { }

    Character::Character(CharacterType const *type) :
        type(type),
        techniques(type->techniques),
        equipment(type->equipment),
        alive(true),
        face(1),
        gravity(0.0f, -20.0f),
        touchLeft(false),
        touchRight(false),
        touchDown(false),
        touchUp(false),
        airJumpCount(0)
    { }

    void Character::step(float dt)
    {
        if (touchDown) {
            if (techniques.tripleJump) {
                airJumpCount = 2;
            } else if (techniques.doubleJump) {
                airJumpCount = 1;
            } else {
                airJumpCount = 0;
            }
        } else if (techniques.wallSlide && equipment.tigerClaws &&
                   (touchLeft || touchRight))
        {
            airJumpCount = 0;
        }
        if (controls.jump && !oldControls.jump) {
            if (touchDown) {
                velocity.y = type->jumpVelocity;
            } else if (techniques.wallSlide && equipment.tigerClaws &&
                       (touchLeft || touchRight))
            {
                if (techniques.wallJump) {
                    int jumpFace = int(touchLeft) - int(touchRight);
                    if (jumpFace) {
                        face = jumpFace;
                    }
                    velocity.x = float(jumpFace) * type->wallJumpVelocity.x;
                    velocity.y = type->wallJumpVelocity.y;
                }
            } else {
                if (equipment.ironFan && airJumpCount) {
                    --airJumpCount;
                    velocity.y = type->airJumpVelocity;
                }
            }
        }
        int moveFace = int(controls.right) - int(controls.left);
        if (moveFace) {
            face = moveFace;
        }
        if (touchDown) {
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
        if (!controls.jump) {
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
            } else if (techniques.wallSlide && equipment.tigerClaws &&
                       (touchLeft || touchRight))
            {
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
