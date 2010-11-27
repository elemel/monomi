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
        int face = int(controls.right) - int(controls.left);
        if (state == characterStates::walking) {
            if (face) {
                velocity.x += float(face) * walkAcceleration * dt;
                velocity.x = sign(velocity.x) * std::min(std::abs(velocity.x), maxWalkVelocity);
            } else {
                velocity.x = sign(velocity.x) * std::max(std::abs(velocity.x) - walkAcceleration * dt, 0.0f);
            }
        } else if (state == characterStates::jumping) {
            if (face) {
                float driftVelocity = velocity.x + float(face) * driftAcceleration * dt;
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
    }
}
