#include "block.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    void Block::update(float dt)
    { }

    void Block::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawBox(box);
    }
}
