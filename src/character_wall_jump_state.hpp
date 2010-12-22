#ifndef MONOMI_CHARACTER_WALL_JUMP_STATE_HPP
#define MONOMI_CHARACTER_WALL_JUMP_STATE_HPP

#include "state.hpp"

namespace monomi {
    class CharacterActor;
    class Game;

    class CharacterWallJumpState :
        public State
    {
    public:
        CharacterWallJumpState(CharacterActor *character, Game *game);

        void enter();
        boost::shared_ptr<State> transition();
        void update(float dt);
        void exit();

    private:
        CharacterActor *character_;
        Game *game_;
    };
}

#endif // MONOMI_CHARACTER_WALL_JUMP_STATE_HPP
