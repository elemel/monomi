#include "block_actor.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    Priority BlockActor::priority() const
    {
        return priorityCount;
    }

    bool BlockActor::alive() const
    {
        return true;
    }

    void BlockActor::update(float dt)
    { }

    void BlockActor::handleCollisions()
    { }

    void BlockActor::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawBox(box);
    }
}
