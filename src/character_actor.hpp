#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "actor.hpp"
#include "control.hpp"
#include "geometry.hpp"
#include "technique.hpp"
#include "tool.hpp"

#include <bitset>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class CharacterType;
    class DebugGraphics;
    class Game;
    class StateMachine;

    class CharacterActor :
        public Actor
    {
    public:
        Game *game;
        boost::shared_ptr<CharacterType const> type;
        std::bitset<techniqueCount> techniques;
        std::bitset<toolCount> tools;

        bool alive_;

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

        boost::shared_ptr<StateMachine> stateMachine_;

        explicit CharacterActor(Game *game, boost::shared_ptr<CharacterType const> const &type);

        Circle bottomCircle() const;
        Circle topCircle() const;

        bool alive() const;
        void update(float dt);
        void handleCollisions();
        void debugDraw(DebugGraphics *debugGraphics);

    private:
        void updatePhysics(float dt);
        void applyConstraints();
        void updateTouchFlags();
    };
}

#endif // MONOMI_CHARACTER_HPP