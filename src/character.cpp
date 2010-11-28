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
        jump(false)
    { }

    Character::Character() :
        face(1),
        circle(Point2(), 0.75f),
        gravity(0.0f, -20.0f),
        state(characterStates::walking),
        walkAcceleration(10.0f),
        maxWalkVelocity(5.0f),
        driftAcceleration(10.0f),
        maxDriftVelocity(3.0f)
    { }

    void Character::step(float dt)
    {
        if (controls.jump) {
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
                if (std::abs(driftVelocity) >= std::abs(velocity.x)) {
                    driftVelocity = sign(driftVelocity) * std::min(std::abs(driftVelocity), maxDriftVelocity);
                }
                velocity.x = driftVelocity;
            }
        }
        velocity += dt * gravity;
        if (state == characterStates::jumping && !controls.jump) {
                velocity.y = std::min(velocity.y, 3.0f);
        }
        circle.center += dt * velocity;
    }

    void Character::debugDraw(DebugGraphics *debugGraphics)
    {
        DebugColor color = (state == characterStates::walking) ? debugColors::green() : debugColors::red();
        debugGraphics->drawCircle(circle, color);
        Point2 faceCenter = circle.center + circle.radius * Vector2(0.3f * float(face), 0.3f);
        debugGraphics->drawCircle(Circle(faceCenter, 0.3f * circle.radius), color);
    }
}
