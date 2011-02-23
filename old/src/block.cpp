#include "block.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    void Block::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawBox(box);
    }
}
