#include "block_actor.hpp"

#include "debug_graphics.hpp"

namespace monomi {
    boost::shared_ptr<Component> BlockActor::physicsComponent()
    {
        return boost::shared_ptr<Component>();
    }

    boost::shared_ptr<Component> BlockActor::collisionComponent()
    {
        return boost::shared_ptr<Component>();
    }

    void BlockActor::update(float dt)
    { }

    void BlockActor::debugDraw(DebugGraphics *debugGraphics)
    {
        debugGraphics->drawBox(box);
    }
}
