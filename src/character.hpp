#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "geometry.hpp"

namespace monomi {
    class DebugGraphics;

    class CharacterControls {
    public:
        CharacterControls();

        bool left;
        bool right;
        bool up;
        bool down;
        bool jump;
    };

    class Character {
    public:
        Point2 position;
        Vector2 velocity;
        Vector2 gravity;
        CharacterControls controls;

        Character();

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP