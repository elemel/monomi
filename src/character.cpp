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
        gravity(0.0f, -10.0f)
    { }

    void Character::step(float dt)
    {
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
        if (controls.jump) {
            std::cout << "jump" << std::endl;
        }
        velocity += dt * gravity;
        circle.center += dt * velocity;
    }

    void Character::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawCircle(circle);
    }
}
