#include "block_actor.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    void BlockActor::update(float dt)
    { }

    void BlockActor::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawBox(box);
    }
}
