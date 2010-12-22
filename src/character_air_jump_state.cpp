#include "character_air_jump_state.hpp"

#include "character_actor.hpp"
#include "character_fall_state.hpp"
#include "character_type.hpp"

namespace monomi {
    CharacterAirJumpState::CharacterAirJumpState(CharacterActor *character,
                                                 Game *game) :
        character_(character),
        game_(game)
    { }    

    void CharacterAirJumpState::enter()
    {
        --character_->airJumpCount;
        character_->velocity.y = character_->type->airJumpVelocity;
    }

    boost::shared_ptr<State> CharacterAirJumpState::transition()
    {
        return boost::shared_ptr<State>(new CharacterFallState(character_, game_));
    }

    void CharacterAirJumpState::update(float dt)
    { }

    void CharacterAirJumpState::exit()
    { }
}
