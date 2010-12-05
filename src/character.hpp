#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "geometry.hpp"

#include <bitset>

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

    enum Technique {
        ambushTechnique,
        chargeTechnique,
        diveTechnique,
        disguiseTechnique,
        doubleJumpTechnique,
        dropTechnique,
        ledgeGrabTechnique,
        ledgeJumpTechnique,
        runTechnique,
        slowFallTechnique,
        splitTechnique,
        sprintTechnique,
        stompTechnique,
        swimTechnique,
        teleportTechnique,
        tripleJumpTechnique,
        wallJumpTechnique,
        wallSlideTechnique,

        techniqueCount
    };

    enum Tool {
        airSkinTool,
        bambooFluteTool,
        grapplingHookTool,
        ironFanTool,
        smokeBombTool,
        strawBasketTool,
        tigerClawTool,
        throwingStarTool,

        toolCount
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
        std::bitset<techniqueCount> techniques;
        std::bitset<toolCount> tools;

        CharacterType();
    };

    class Character {
    public:
        CharacterType const *type;
        std::bitset<techniqueCount> techniques;
        std::bitset<toolCount> tools;

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