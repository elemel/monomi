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
        bool left;
        bool right;
        bool up;
        bool down;
        bool jump;
        bool action;

        CharacterControls();
    };

    class CharacterType {
    public:
        int key;
        float radius;
        float maxVelocity;
        float walkAcceleration;
        float maxWalkVelocity;
        float driftAcceleration;
        float maxDriftVelocity;
        float jumpVelocity;
        Vector2 wallJumpVelocity;
        float airJumpVelocity;
        float maxAirJumpCount;

        CharacterType();
    };

    class Character {
    public:
        CharacterType const *type;
        bool alive;

        // Track which direction the character faces, -1 for left and +1 for
        // right.
        int face;

        Point2 position;
        Vector2 velocity;
        Vector2 gravity;
        CharacterState state;
        CharacterControls controls;
        CharacterControls oldControls;
        bool touchingLeftWall;
        bool touchingRightWall;
        bool touchingCeiling;
        bool touchingFloor;
        int airJumpCount;

        explicit Character(CharacterType const *type);

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP