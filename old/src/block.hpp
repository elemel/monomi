#ifndef MONOMI_BLOCK_HPP
#define MONOMI_BLOCK_HPP

#include "geometry.hpp"

namespace monomi {
    class DebugGraphics;

    class Block {
    public:
        Box2 box;

        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_BLOCK_HPP
