#include "character.hpp"

#include "debug_graphics.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterControls::CharacterControls() :
        left(false),
        right(false),
        up(false),
        down(false),
        jump(false),
        action(false)
    { }

    Character::Character() :
        alive(true),
        face(1),
        circle(Point2(), 0.75f),
        gravity(0.0f, -20.0f),
        state(characterStates::walking),
        walkAcceleration(9.0f),
        maxWalkVelocity(6.0f),
        driftAcceleration(6.0f),
        maxDriftVelocity(3.0f),
        maxVelocity(20.0f),
        touchingLeftWall(false),
        touchingRightWall(false),
        touchingCeiling(false),
        touchingFloor(false)
    { }

    void Character::step(float dt)
    {
        if (controls.jump && !oldControls.jump) {
            if (state == characterStates::walking) {
                state = characterStates::jumping;
                velocity.y += 12.0f;
            }
        }
        int moveFace = int(controls.right) - int(controls.left);
        if (moveFace) {
            face = moveFace;
        }
        if (state == characterStates::walking) {
            if (moveFace) {
                velocity.x += float(moveFace) * walkAcceleration * dt;
                velocity.x = sign(velocity.x) * std::min(std::abs(velocity.x), maxWalkVelocity);
            } else {
                velocity.x = sign(velocity.x) * std::max(std::abs(velocity.x) - walkAcceleration * dt, 0.0f);
            }
        } else if (state == characterStates::jumping) {
            if (moveFace) {
                float driftVelocity = velocity.x + float(moveFace) * driftAcceleration * dt;
                velocity.x = sign(driftVelocity) * std::min(std::abs(driftVelocity), std::max(std::abs(velocity.x), maxDriftVelocity));
            }
        }
        velocity += dt * gravity;
        if (state == characterStates::jumping && !controls.jump) {
            velocity.y = std::min(velocity.y, 3.0f);
        }
        if (velocity.squaredLength() >= maxVelocity * maxVelocity) {
            velocity.normalize();
            velocity *= maxVelocity;
        }
        circle.center += dt * velocity;
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
        debugGraphics->drawCircle(circle, color);
        Point2 eyeCenter1 = circle.center + circle.radius * Vector2(0.1f * float(face), 0.3f);
        Point2 eyeCenter2 = circle.center + circle.radius * Vector2(0.4f * float(face), 0.3f);
        debugGraphics->drawCircle(Circle(eyeCenter1, 0.1f * circle.radius), color);
        debugGraphics->drawCircle(Circle(eyeCenter2, 0.1f * circle.radius), color);
    }
}
