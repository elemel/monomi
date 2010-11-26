#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "geometry.hpp"

namespace monomi {
    class DebugGraphics;

    namespace characterStates {
        enum CharacterState {
            climbing,
            crouching,
            jumping,
            standing,
            walking,
            wallSliding
        };
    }

    using characterStates::CharacterState;

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
        Circle circle;
        Vector2 velocity;
        Vector2 gravity;
        CharacterState state;
        CharacterControls controls;

        Character();

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP