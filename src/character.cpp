#include "character.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    void Character::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawCircle(Circle(position, 0.75f));
    }
}
