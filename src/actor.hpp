#ifndef MONOMI_ACTOR_HPP
#define MONOMI_ACTOR_HPP

#include <boost/shared_ptr.hpp>

namespace monomi {
    class Component;
    class DebugGraphics;

    class Actor {
    public:
        virtual ~Actor();

        virtual boost::shared_ptr<Component> stateComponent() = 0;
        virtual boost::shared_ptr<Component> physicsComponent() = 0;
        virtual boost::shared_ptr<Component> collisionComponent() = 0;

        virtual bool alive() const = 0;
        virtual void debugDraw(DebugGraphics *debugGraphics) = 0;
    };
}

#endif // MONOMI_ACTOR_HPP
