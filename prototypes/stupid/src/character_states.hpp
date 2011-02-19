#ifndef MONOMI_CHARACTER_STATES_HPP
#define MONOMI_CHARACTER_STATES_HPP

#include "state.hpp"

namespace monomi {
    class CharacterActor;

    // FALL ///////////////////////////////////////////////////////////////////

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
    
    // JUMP ///////////////////////////////////////////////////////////////////

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

    // RUN ////////////////////////////////////////////////////////////////////

    class CharacterRunState : public State {
    public:
        explicit CharacterRunState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterRunState::CharacterRunState(CharacterActor *character) :
        character_(character)
    { }

    // STAND //////////////////////////////////////////////////////////////////

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

    // STOMP //////////////////////////////////////////////////////////////////

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

    // WALK ///////////////////////////////////////////////////////////////////

    class CharacterWalkState : public State {
    public:
        explicit CharacterWalkState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterWalkState::CharacterWalkState(CharacterActor *character) :
        character_(character)
    { }

    // WALL JUMP ///////////////////////////////////////////////////////////////

    class CharacterWallJumpState : public State {
    public:
        explicit CharacterWallJumpState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;

    private:
        CharacterActor *character_;
    };

    inline CharacterWallJumpState::CharacterWallJumpState(CharacterActor *character) :
        character_(character)
    { }

    // WALL RUN ///////////////////////////////////////////////////////////////

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

    // WALL SLIDE /////////////////////////////////////////////////////////////

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
