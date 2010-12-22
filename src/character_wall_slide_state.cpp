#include "character_wall_slide_state.hpp"

#include "character_actor.hpp"
#include "character_jump_state.hpp"
#include "character_type.hpp"
#include "character_walk_state.hpp"

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
        if (character_->controls.test(jumpControl) &&
            !character_->oldControls.test(jumpControl) &&
            character_->techniques.test(wallJumpTechnique))
        {
            int jumpFace = int(character_->touchLeft) - int(character_->touchRight);
            if (jumpFace) {
                character_->face = jumpFace;
            }
            character_->velocity.x = float(jumpFace) * character_->type->wallJumpVelocity.x;
            character_->velocity.y = character_->type->wallJumpVelocity.y;
            return boost::shared_ptr<State>(new CharacterJumpState(character_, game_));
        } else if (character_->touchDown) {
            return boost::shared_ptr<State>(new CharacterWalkState(character_, game_));
        } else if (!character_->touchLeft && !character_->touchRight ||
                   !character_->touchLeft && character_->controls.test(leftControl) ||
                   !character_->touchRight && character_->controls.test(rightControl))
        {
            return boost::shared_ptr<State>(new CharacterJumpState(character_, game_));
        } else {
            return boost::shared_ptr<State>();
        }
    }

    void CharacterWallSlideState::update(float dt)
    {
        int slideFace = (int(character_->touchLeft) -
                         int(character_->touchRight));
        if (slideFace) {
            character_->face = slideFace;
        }
        if (!character_->controls.test(jumpControl)) {
            character_->velocity.y = std::min(character_->velocity.y, 3.0f);
        }
    }

    void CharacterWallSlideState::exit()
    { }
}
