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

    class CharacterStompState : public State {
    public:
        explicit CharacterStompState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterStompState::CharacterStompState(CharacterActor *character) :
        character_(character)
    { }

    class CharacterWallRunState : public State {
    public:
        explicit CharacterWallRunState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterWallRunState::CharacterWallRunState(CharacterActor *character) :
        character_(character)
    { }

    class CharacterWallSlideState : public State {
    public:
        explicit CharacterWallSlideState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterWallSlideState::CharacterWallSlideState(CharacterActor *character) :
        character_(character)
    { }
}

#endif // MONOMI_CHARACTER_STATES_HPP
