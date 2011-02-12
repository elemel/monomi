#include "character_actor.hpp"

#include "state.hpp"

#include <iostream>

namespace monomi {
    void CharacterActor::update(float dt)
    {
        if (CharacterActor::StatePtr state = state_->transition()) {
            state_->leave();
            state_ = state;
            std::cerr << "DEBUG: Character changed state." << std::endl;
            state_->enter();
        }
        state_->update(dt);
    }
}
