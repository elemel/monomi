#ifndef MONOMI_CHARACTER_FALL_STATE_HPP
#define MONOMI_CHARACTER_FALL_STATE_HPP

#include "state.hpp"

namespace monomi {
    class CharacterActor;
    class Game;

    class CharacterFallState :
        public State
    {
    public:
        CharacterFallState(CharacterActor *character, Game *game);

        void enter();
        boost::shared_ptr<State> transition();
        void update(float dt);
        void exit();

    private:
        CharacterActor *character_;
        Game *game_;
        bool oldJumpInput_;
    };
}

#endif // MONOMI_CHARACTER_FALL_STATE_HPP
