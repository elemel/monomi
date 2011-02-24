#ifndef MONOMI_CHARACTER_STATES_HPP
#define MONOMI_CHARACTER_STATES_HPP

#include "state.hpp"

namespace monomi {
    class CharacterActor;

    class CharacterState : public State {
    public:
        explicit CharacterState(CharacterActor *character);

    protected:
        CharacterActor *character_;
    };

    inline CharacterState::CharacterState(CharacterActor *character) :
        character_(character)
    { }

    // CEILING RUN ////////////////////////////////////////////////////////////

    class CharacterCeilingRunState : public CharacterState {
    public:
        explicit CharacterCeilingRunState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterCeilingRunState::CharacterCeilingRunState(CharacterActor *character) :
        CharacterState(character)
    { }

    // FALL ///////////////////////////////////////////////////////////////////

    class CharacterFallState : public CharacterState {
    public:
        explicit CharacterFallState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterFallState::CharacterFallState(CharacterActor *character) :
        CharacterState(character)
    { }
    
    // JUMP ///////////////////////////////////////////////////////////////////

    class CharacterJumpState : public CharacterState {
    public:
        explicit CharacterJumpState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterJumpState::CharacterJumpState(CharacterActor *character) :
        CharacterState(character)
    { }

    // RUN ////////////////////////////////////////////////////////////////////

    class CharacterRunState : public CharacterState {
    public:
        explicit CharacterRunState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterRunState::CharacterRunState(CharacterActor *character) :
        CharacterState(character)
    { }

    // STAND //////////////////////////////////////////////////////////////////

    class CharacterStandState : public CharacterState {
    public:
        explicit CharacterStandState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterStandState::CharacterStandState(CharacterActor *character) :
        CharacterState(character)
    { }

    // STOMP //////////////////////////////////////////////////////////////////

    class CharacterStompState : public CharacterState {
    public:
        explicit CharacterStompState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterStompState::CharacterStompState(CharacterActor *character) :
        CharacterState(character)
    { }

    // WALK ///////////////////////////////////////////////////////////////////

    class CharacterWalkState : public CharacterState {
    public:
        explicit CharacterWalkState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterWalkState::CharacterWalkState(CharacterActor *character) :
        CharacterState(character)
    { }

    // WALL JUMP ///////////////////////////////////////////////////////////////

    class CharacterWallJumpState : public CharacterState {
    public:
        explicit CharacterWallJumpState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterWallJumpState::CharacterWallJumpState(CharacterActor *character) :
        CharacterState(character)
    { }

    // WALL RUN ///////////////////////////////////////////////////////////////

    class CharacterWallRunState : public CharacterState {
    public:
        explicit CharacterWallRunState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterWallRunState::CharacterWallRunState(CharacterActor *character) :
        CharacterState(character)
    { }

    // WALL SLIDE /////////////////////////////////////////////////////////////

    class CharacterWallSlideState : public CharacterState {
    public:
        explicit CharacterWallSlideState(CharacterActor *character);

        void enter();
        void leave();

        StatePtr transition();
        void update(float dt);

        void print(std::ostream &out) const;
    };

    inline CharacterWallSlideState::CharacterWallSlideState(CharacterActor *character) :
        CharacterState(character)
    { }
}

#endif // MONOMI_CHARACTER_STATES_HPP
