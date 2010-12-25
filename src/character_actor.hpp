#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"
#include "contact.hpp"
#include "geometry.hpp"
#include "input.hpp"
#include "technique.hpp"
#include "tool.hpp"

#include <bitset>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

namespace monomi {
    class CharacterType;
    class DebugGraphics;
    class Game;
    class StateMachine;

    class CharacterActor :
        public Actor
    {
    public:
        typedef std::bitset<techniqueCount> TechniqueBits;
        typedef std::bitset<toolCount> ToolBits;
        typedef std::bitset<inputCount> InputBits;
        typedef std::bitset<contactCount> ContactBits;

        typedef boost::signal<void ()> ContactSignal;
        typedef ContactSignal::slot_type ContactSlot;

        TechniqueBits techniques;
        ToolBits tools;

        // Track which direction the character faces, -1 for left and +1 for
        // right.
        int face;

        Point2 position;
        Vector2 velocity;
        Vector2 gravity;
        InputBits inputs;
        InputBits oldInputs;
        ContactBits contacts;
        int airJumpCount;

        CharacterType const *type() const;

        Circle bottomCircle() const;
        Circle topCircle() const;

        bool alive() const;
        void update(float dt);
        void handleCollisions();
        void debugDraw(DebugGraphics *debugGraphics);

    private:
        friend class CharacterFactory;

        Game *game_;
        CharacterType const *type_;
        bool alive_;
        boost::shared_ptr<StateMachine> stateMachine_;
        ContactSignal contactSignal_;

        CharacterActor(Game *game, CharacterType const *type);

        void updatePhysics(float dt);
        void applyConstraints();
        void updateContacts();

        void onTransition();
    };
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
