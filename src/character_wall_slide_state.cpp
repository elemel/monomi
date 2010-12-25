#include "character_wall_slide_state.hpp"

#include "character_actor.hpp"
#include "character_fall_state.hpp"
#include "character_type.hpp"
#include "character_walk_state.hpp"
#include "character_wall_jump_state.hpp"

namespace monomi {
    CharacterWallSlideState::CharacterWallSlideState(CharacterActor *character, Game *game) :
        character_(character),
        game_(game),
        oldJumpInput_(false)
    { }    

    void CharacterWallSlideState::enter()
    {
        character_->airJumpCount = 0;
        oldJumpInput_ = character_->testInput(jumpInput);
    }

    boost::shared_ptr<State> CharacterWallSlideState::transition()
    {
        if (character_->testInput(jumpInput) && !oldJumpInput_ &&
            character_->testTechnique(wallJumpTechnique))
        {
            return boost::shared_ptr<State>(new CharacterWallJumpState(character_, game_));
        } else if (character_->testContact(downContact)) {
            return boost::shared_ptr<State>(new CharacterWalkState(character_, game_));
        } else if (!character_->testContact(leftContact) &&
                   !character_->testContact(rightContact) ||
                   !character_->testContact(leftContact) &&
                   character_->testInput(leftInput) ||
                   !character_->testContact(rightContact) &&
                   character_->testInput(rightInput))
        {
            return boost::shared_ptr<State>(new CharacterFallState(character_, game_));
        } else {
            return boost::shared_ptr<State>();
        }
    }

    void CharacterWallSlideState::update(float dt)
    {
        int slideFace = (int(character_->testContact(leftContact)) -
                         int(character_->testContact(rightContact)));
        if (slideFace) {
            character_->face = slideFace;
        }
        if (!character_->testInput(jumpInput)) {
            character_->velocity.y = std::min(character_->velocity.y, 3.0f);
        }
        oldJumpInput_ = character_->testInput(jumpInput);
    }

    void CharacterWallSlideState::exit()
    { }
}
