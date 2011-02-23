#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "geometry.hpp"

namespace monomi {
    class DebugGraphics;

    namespace characterStates {
        enum CharacterState {
            crouching,
            diving,
            jumping,
            ledgeHanging,
            running,
            sliding,
            stalking,
            swimming,
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
        bool action;
    };

    class Character {
    public:
        bool alive;

        // Track which direction the character faces, -1 for left and +1 for
        // right.
        int face;

        Circle circle;
        Vector2 velocity;
        Vector2 gravity;
        CharacterState state;
        CharacterControls controls;
        CharacterControls oldControls;
        float walkAcceleration;
        float maxWalkVelocity;
        float driftAcceleration;
        float maxDriftVelocity;
        float maxVelocity;
        bool touchingLeftWall;
        bool touchingRightWall;
        bool touchingCeiling;
        bool touchingFloor;
        int airJumpCount;
        int maxAirJumpCount;

        Character();

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP