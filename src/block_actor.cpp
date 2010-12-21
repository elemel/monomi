#include "block_actor.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    boost::shared_ptr<Component> BlockActor::stateComponent()
    {
        return boost::shared_ptr<Component>();
    }

    boost::shared_ptr<Component> BlockActor::physicsComponent()
    {
        return boost::shared_ptr<Component>();
    }

    boost::shared_ptr<Component> BlockActor::collisionComponent()
    {
        return boost::shared_ptr<Component>();
    }

    bool BlockActor::alive() const
    {
        return true;
    }

    void BlockActor::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawBox(box);
    }
}
