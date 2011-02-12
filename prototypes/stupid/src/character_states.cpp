#include "character_states.hpp"

namespace monomi {
    boost::shared_ptr<State> CharacterFallState::transition()
    {
        return boost::shared_ptr<State>();
    }

    void CharacterFallState::update(float dt)
    {
        (void) dt;
    }
}
