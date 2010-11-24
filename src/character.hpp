#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "geometry.hpp"

namespace monomi {
    class DebugGraphics;

    class Character {
    public:
        Point2 position;

        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP