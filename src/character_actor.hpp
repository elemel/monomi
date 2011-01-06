#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"
#include "contact.hpp"
#include "geometry.hpp"
#include "input.hpp"
#include "technique.hpp"
#include "tool.hpp"

#include <bitset>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

namespace monomi {
    class CharacterType;
    class DebugGraphics;
    class Game;
    class StateMachine;

    class CharacterActor :
        public Actor,
        private boost::noncopyable
    {
    public:
        typedef std::bitset<techniqueCount> TechniqueBits;
        typedef std::bitset<toolCount> ToolBits;
        typedef std::bitset<inputCount> InputBits;
        typedef std::bitset<contactCount> ContactBits;

        typedef boost::signals2::signal<void ()> ContactSignal;
        typedef ContactSignal::slot_type ContactSlot;

        typedef boost::signals2::signal<void ()> InputSignal;
        typedef InputSignal::slot_type InputSlot;

        typedef boost::signals2::signal<void ()> StateTransitionSignal;
        typedef StateTransitionSignal::slot_type StateTransitionSlot;

        // Track which direction the character faces, -1 for left and +1 for
        // right.
        int face;

        Point2 position;
        Vector2 velocity;
        Vector2 gravity;
        int airJumpCount;

        CharacterType const *type() const;

        bool testTechnique(Technique technique) const;
        void setTechnique(Technique technique, bool value);

        bool testTool(Tool tool) const;
        void setTool(Tool tool, bool value);

        bool testContact(Contact contact) const;
        void setContact(Contact contact, bool value);

        bool testInput(Input input) const;
        void setInput(Input input, bool value);

        Circle bottomCircle() const;
        Circle topCircle() const;

        Priority priority() const;
        bool alive() const;
        void update(float dt);
        void handleCollisions();
        void debugDraw(DebugGraphicsPtr const &graphics) const;

        boost::signals2::connection
        connectContactSlot(ContactSlot const &slot);

        boost::signals2::connection
        connectInputSlot(InputSlot const &slot);

        boost::signals2::connection
        connectStateTransitionSlot(StateTransitionSlot const &slot);

    private:
        friend class CharacterFactory;

        Game *game_;
        CharacterType const *type_;

        TechniqueBits techniques_;
        ToolBits tools_;
        ContactBits contacts_;
        InputBits inputs_;

        bool alive_;
        boost::shared_ptr<StateMachine> stateMachine_;
        ContactSignal contactSignal_;
        InputSignal inputSignal_;

        CharacterActor(Game *game, CharacterType const *type);

        void updatePhysics(float dt);
        void applyConstraints();
        void updateContacts();

        void onTransition();
    };
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
