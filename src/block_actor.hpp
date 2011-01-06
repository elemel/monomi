#ifndef MONOMI_BLOCK_HPP
#define MONOMI_BLOCK_HPP

#include "actor.hpp"
#include "geometry.hpp"

#include <boost/shared_ptr.hpp>

namespace monomi {
    class BlockActor :
        public Actor
    {
    public:
        Box2 box;

        Priority priority() const;
        bool alive() const;
        void update(float dt);
        void handleCollisions();
        void debugDraw(DebugGraphicsPtr const &graphics) const;
    };
}

#endif // MONOMI_BLOCK_HPP
