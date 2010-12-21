#ifndef MONOMI_CHARACTER_STATE_COMPONENT_HPP
#define MONOMI_CHARACTER_STATE_COMPONENT_HPP

#include "component.hpp"

#include <boost/shared_ptr.hpp>

namespace monomi {
    class CharacterActor;
    class Game;
    class State;

    class CharacterStateComponent :
        public Component
    {
    public:
        CharacterStateComponent(CharacterActor *character, Game *game,
                                boost::shared_ptr<State> const &state);

        void update(float dt);

    private:
        CharacterActor *character_;
        Game *game_;
        boost::shared_ptr<State> state_;
    };
}

#endif // MONOMI_CHARACTER_STATE_COMPONENT_HPP
