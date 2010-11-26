#include "character.hpp"

#include "debug_graphics.hpp"

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
        gravity(0.0f, -15.0f),
        state(characterStates::standing)
    { }

    void Character::step(float dt)
    {
        if (controls.jump) {
            if (state == characterStates::standing) {
                state = characterStates::jumping;
                velocity.y += 10.0f;
            }
        }
        if (controls.left) {
            std::cout << "left" << std::endl;
        }
        if (controls.right) {
            std::cout << "right" << std::endl;
        }
        if (controls.up) {
            std::cout << "up" << std::endl;
        }
        if (controls.down) {
            std::cout << "down" << std::endl;
        }
        velocity += dt * gravity;
        if (state == characterStates::jumping && !controls.jump) {
                velocity.y = std::min(velocity.y, 3.0f);
        }
        circle.center += dt * velocity;
    }

    void Character::debugDraw(DebugGraphics *debugGraphics)
    {
        DebugColor color = (state == characterStates::standing) ? debugColors::green() : debugColors::red();
        debugGraphics->drawCircle(circle, color);
    }
}
