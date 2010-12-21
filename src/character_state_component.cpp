#include "character_state_component.hpp"

#include "character_actor.hpp"
#include "state.hpp"

namespace monomi {
    CharacterStateComponent::CharacterStateComponent(CharacterActor *character,
                                                     Game *game,
                                                     boost::shared_ptr<State> const &state) :
        character_(character),
        game_(game),
        state_(state)
    { }

    void CharacterStateComponent::update(float dt)
    {
        if (character_->alive_) {
            if (boost::shared_ptr<State> newState = state_->transition()) {
                state_->exit();
                state_ = newState;
                state_->enter();
            }
            state_->update(dt);
        }

        // Copy controls.
        character_->oldControls = character_->controls;
    }
}
