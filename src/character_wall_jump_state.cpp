#include "character_wall_jump_state.hpp"

#include "character_actor.hpp"
#include "character_fall_state.hpp"
#include "character_type.hpp"

namespace monomi {
    CharacterWallJumpState::CharacterWallJumpState(CharacterActor *character,
                                                   Game *game) :
        character_(character),
        game_(game)
    { }    

    void CharacterWallJumpState::enter()
    {
        int jumpFace = (int(character_->contacts.test(leftContact)) -
                        int(character_->contacts.test(rightContact)));
        if (jumpFace) {
            character_->face = jumpFace;
        }
        character_->velocity.x = float(jumpFace) * character_->type()->wallJumpVelocity.x;
        character_->velocity.y = character_->type()->wallJumpVelocity.y;
    }

    boost::shared_ptr<State> CharacterWallJumpState::transition()
    {
        return boost::shared_ptr<State>(new CharacterFallState(character_, game_));
    }

    void CharacterWallJumpState::update(float dt)
    { }

    void CharacterWallJumpState::exit()
    { }
}
