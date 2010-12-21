#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

#include <boost/shared_ptr.hpp>

namespace monomi {
    class Component;
    class DebugGraphics;

    class Actor {
    public:
        virtual ~Actor();

        virtual boost::shared_ptr<Component> physicsComponent() = 0;

        virtual bool alive() const = 0;
        virtual void update(float dt) = 0;
        virtual void handleCollisions() = 0;
        virtual void debugDraw(DebugGraphics *debugGraphics) = 0;
    };
}

#endif // MONOMI_ACTOR_HPP
