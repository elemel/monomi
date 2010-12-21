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
    class Component;
    class DebugGraphics;

    class CharacterActor :
        public Actor
    {
    public:
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

        boost::shared_ptr<Component> stateComponent_;
        boost::shared_ptr<Component> physicsComponent_;
        boost::shared_ptr<Component> collisionComponent_;

        explicit CharacterActor(boost::shared_ptr<CharacterType const> const &type);

        bool wallSliding() const;
        Circle bottomCircle() const;
        Circle topCircle() const;

        boost::shared_ptr<Component> stateComponent();
        boost::shared_ptr<Component> physicsComponent();
        boost::shared_ptr<Component> collisionComponent();

        bool alive() const;
        void debugDraw(DebugGraphics *debugGraphics);
    };
}

#endif // MONOMI_CHARACTER_HPP