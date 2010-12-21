#ifndef MONOMI_CHARACTER_STATE_COMPONENT_HPP
#define MONOMI_CHARACTER_STATE_COMPONENT_HPP

#include "component.hpp"

namespace monomi {
    class CharacterActor;
    class Game;

    class CharacterStateComponent :
        public Component
    {
    public:
        explicit CharacterStateComponent(CharacterActor *character,
                                         Game *game);

        void update(float dt);

    private:
        CharacterActor *character_;
        Game *game_;
    };
}

#endif // MONOMI_CHARACTER_STATE_COMPONENT_HPP
