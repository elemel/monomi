#include "character_jump_state.hpp"

#include "character_actor.hpp"
#include "character_fall_state.hpp"
#include "character_type.hpp"

namespace monomi {
    CharacterJumpState::CharacterJumpState(CharacterActor *character,
                                           Game *game) :
        character_(character),
        game_(game)
    { }    

    void CharacterJumpState::enter()
    {
        character_->velocity.y = character_->type()->jumpVelocity;
    }

    boost::shared_ptr<State> CharacterJumpState::transition()
    {
        return boost::shared_ptr<State>(new CharacterFallState(character_, game_));
    }

    void CharacterJumpState::update(float dt)
    { }

    void CharacterJumpState::exit()
    { }
}
