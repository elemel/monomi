#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "actor.hpp"
#include "control.hpp"
#include "geometry.hpp"
#include "technique.hpp"
#include "tool.hpp"

#include <bitset>

namespace monomi {
    class CharacterType;
    class DebugGraphics;

    class Character :
        public Actor
    {
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
        Circle bottomCircle() const;
        Circle topCircle() const;

        void step(float dt);
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP