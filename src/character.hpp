#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "geometry.hpp"

namespace monomi {
    class DebugGraphics;

    class CharacterControls {
    public:
        bool left : 1;
        bool right : 1;
        bool down : 1;
        bool up : 1;
        bool jump : 1;
        bool action : 1;

        CharacterControls();
    };

    class Techniques {
    public:
        bool ambush : 1;
        bool charge : 1;
        bool dive : 1;
        bool disguise : 1;
        bool doubleJump : 1;
        bool drop : 1;
        bool ledgeGrab : 1;
        bool ledgeJump : 1;
        bool run : 1;
        bool slam : 1;
        bool slowFall : 1;
        bool split : 1;
        bool sprint : 1;
        bool swim : 1;
        bool teleport : 1;
        bool tripleJump : 1;
        bool wallJump : 1;
        bool wallSlide : 1;

        Techniques();
    };

    class Equipment {
    public:
        bool airSkin : 1;
        bool bambooFlute : 1;
        bool grapplingHook : 1;
        bool ironFan : 1;
        bool smokeBombs : 1;
        bool strawBasket : 1;
        bool tigerClaws : 1;
        bool throwingStars : 1;

        Equipment();
    };

    class CharacterType {
    public:
        float radius;
        float maxVelocity;
        float walkAcceleration;
        float maxWalkVelocity;
        float driftAcceleration;
        float maxDriftVelocity;
        float jumpVelocity;
        Vector2 wallJumpVelocity;
        float airJumpVelocity;
        Techniques techniques;
        Equipment equipment;

        CharacterType();
    };

    class Character {
    public:
        CharacterType const *type;
        Techniques techniques;
        Equipment equipment;

        bool alive;

        // Track which direction the character faces, -1 for left and +1 for
        // right.
        int face;

        Point2 position;
        Vector2 velocity;
        Vector2 gravity;
        CharacterControls controls;
        CharacterControls oldControls;
        bool touchLeft;
        bool touchRight;
        bool touchDown;
        bool touchUp;
        int airJumpCount;

        explicit Character(CharacterType const *type);

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP