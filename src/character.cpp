#include "character.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    CharacterControls::CharacterControls() :
        left(false),
        right(false),
        up(false),
        down(false),
        jump(false)
    { }

    Character::Character() :
        gravity(0.0f, -10.0f)
    { }

    void Character::step(float dt)
    {
        velocity += dt * gravity;
        position += dt * velocity;
    }

    void Character::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawCircle(Circle(position, 0.75f));
    }
}
