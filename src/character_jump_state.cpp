#include "character_jump_state.hpp"

#include "character_actor.hpp"
#include "character_type.hpp"
#include "character_walk_state.hpp"
#include "character_wall_slide_state.hpp"

#include <cmath>

namespace monomi {
    CharacterJumpState::CharacterJumpState(CharacterActor *character,
                                           Game *game) :
        character_(character),
        game_(game)
    { }    

    void CharacterJumpState::enter()
    { }

    boost::shared_ptr<State> CharacterJumpState::transition()
    {
        if (character_->controls.test(jumpControl) &&
            !character_->oldControls.test(jumpControl) &&
            character_->tools.test(ironFanTool) && character_->airJumpCount)
        {
            --character_->airJumpCount;
            character_->velocity.y = character_->type->airJumpVelocity;
            return boost::shared_ptr<State>(new CharacterJumpState(character_, game_));
        } else if (character_->touchDown) {
            return boost::shared_ptr<State>(new CharacterWalkState(character_, game_));
        } else if ((character_->touchLeft || character_->touchRight) &&
                   character_->techniques.test(wallSlideTechnique) &&
                   character_->tools.test(tigerClawTool))
        {
            return boost::shared_ptr<State>(new CharacterWallSlideState(character_, game_));
        } else {
            return boost::shared_ptr<State>();
        }
    }

    void CharacterJumpState::update(float dt)
    {
        int driftFace = (int(character_->controls.test(rightControl)) -
                         int(character_->controls.test(leftControl)));
        if (driftFace) {
            character_->face = driftFace;
        }
        if (driftFace) {
            float driftVelocity = (character_->velocity.x + float(driftFace) *
                                   character_->type->driftAcceleration * dt);
            character_->velocity.x = (sign(driftVelocity) *
                                      std::min(std::abs(driftVelocity),
                                               std::max(std::abs(character_->velocity.x),
                                                        character_->type->maxDriftVelocity)));
        }
        if (!character_->controls.test(jumpControl)) {
            character_->velocity.y = std::min(character_->velocity.y, 3.0f);
        }
    }

    void CharacterJumpState::exit()
    { }
}