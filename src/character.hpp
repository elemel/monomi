#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "control.hpp"
#include "geometry.hpp"

#include <bitset>

namespace monomi {
    class DebugGraphics;

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
        std::bitset<controlCount> controls;
        std::bitset<controlCount> oldControls;
        bool touchLeft;
        bool touchRight;
        bool touchDown;
        bool touchUp;
        int airJumpCount;

        explicit Character(CharacterType const *type);

        bool wallSliding() const;

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP