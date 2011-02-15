#ifndef MONOMI_CHARACTER_STATES_HPP
#define MONOMI_CHARACTER_STATES_HPP

#include "state.hpp"

namespace monomi {
    class CharacterActor;

    class CharacterFallState : public State {
    public:
        explicit CharacterFallState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterFallState::CharacterFallState(CharacterActor *character) :
        character_(character)
    { }
    
    class CharacterJumpState : public State {
    public:
        explicit CharacterJumpState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterJumpState::CharacterJumpState(CharacterActor *character) :
        character_(character)
    { }

    class CharacterStandState : public State {
    public:
        explicit CharacterStandState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterStandState::CharacterStandState(CharacterActor *character) :
        character_(character)
    { }
}

#endif // MONOMI_CHARACTER_STATES_HPP
