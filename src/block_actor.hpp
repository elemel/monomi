#ifndef MONOMI_BLOCK_HPP
#define MONOMI_BLOCK_HPP

#include "actor.hpp"
#include "geometry.hpp"

namespace monomi {
    class DebugGraphics;

    class BlockActor :
        public Actor
    {
    public:
        Box2 box;

        void update(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_BLOCK_HPP
