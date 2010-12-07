#include "block.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    void Block::step(float dt)
    { }

    void Block::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawBox(box);
    }
}
