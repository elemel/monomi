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

        boost::shared_ptr<State> transition();
        void update(float dt);

    private:
        CharacterActor *character_;
    };

    inline CharacterFallState::CharacterFallState(CharacterActor *character) :
        character_(character)
    { }
    
    inline void CharacterFallState::enter()
    { }
    
    inline void CharacterFallState::leave()
    { }
}

#endif // MONOMI_CHARACTER_STATES_HPP
