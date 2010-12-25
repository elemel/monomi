#ifndef MONOMI_CHARACTER_HPP
#define MONOMI_CHARACTER_HPP

#include "actor.hpp"
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

    enum Contact {
        downContact,
        upContact,
        leftContact,
        rightContact,

        contactCount
    };

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

        Game *game;
        CharacterType const *type;
        TechniqueBits techniques;
        ToolBits tools;

        bool alive_;

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

        explicit CharacterActor(Game *game, CharacterType const *type);

        Circle bottomCircle() const;
        Circle topCircle() const;

        bool alive() const;
        void update(float dt);
        void handleCollisions();
        void debugDraw(DebugGraphics *debugGraphics);

    private:
        friend class CharacterFactory;

        boost::shared_ptr<StateMachine> stateMachine_;
        ContactSignal contactSignal_;

        void updatePhysics(float dt);
        void applyConstraints();
        void updateContacts();

        void onTransition();
    };
}

#endif // MONOMI_CHARACTER_HPP
