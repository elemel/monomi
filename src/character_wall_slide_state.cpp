#include "character_wall_slide_state.hpp"

#include "character_actor.hpp"
#include "character_fall_state.hpp"
#include "character_type.hpp"
#include "character_walk_state.hpp"
#include "character_wall_jump_state.hpp"

namespace monomi {
    CharacterWallSlideState::CharacterWallSlideState(CharacterActor *character, Game *game) :
        character_(character),
        game_(game)
    { }    

    void CharacterWallSlideState::enter()
    {
        character_->airJumpCount = 0;
    }

    boost::shared_ptr<State> CharacterWallSlideState::transition()
    {
        if (character_->inputs.test(jumpInput) &&
            !character_->oldInputs.test(jumpInput) &&
            character_->techniques.test(wallJumpTechnique))
        {
            return boost::shared_ptr<State>(new CharacterWallJumpState(character_, game_));
        } else if (character_->contacts.test(downContact)) {
            return boost::shared_ptr<State>(new CharacterWalkState(character_, game_));
        } else if (!character_->contacts.test(leftContact) &&
                   !character_->contacts.test(rightContact) ||
                   !character_->contacts.test(leftContact) &&
                   character_->inputs.test(leftInput) ||
                   !character_->contacts.test(rightContact) &&
                   character_->inputs.test(rightInput))
        {
            return boost::shared_ptr<State>(new CharacterFallState(character_, game_));
        } else {
            return boost::shared_ptr<State>();
        }
    }

    void CharacterWallSlideState::update(float dt)
    {
        int slideFace = (int(character_->contacts.test(leftContact)) -
                         int(character_->contacts.test(rightContact)));
        if (slideFace) {
            character_->face = slideFace;
        }
        if (!character_->inputs.test(jumpInput)) {
            character_->velocity.y = std::min(character_->velocity.y, 3.0f);
        }
    }

    void CharacterWallSlideState::exit()
    { }
}
