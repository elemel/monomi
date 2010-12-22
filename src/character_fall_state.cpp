#include "character_fall_state.hpp"

#include "character_actor.hpp"
#include "character_air_jump_state.hpp"
#include "character_jump_state.hpp"
#include "character_type.hpp"
#include "character_walk_state.hpp"
#include "character_wall_slide_state.hpp"

#include <cmath>

namespace monomi {
    CharacterFallState::CharacterFallState(CharacterActor *character,
                                           Game *game) :
        character_(character),
        game_(game)
    { }    

    void CharacterFallState::enter()
    { }

    boost::shared_ptr<State> CharacterFallState::transition()
    {
        if (character_->controls.test(jumpControl) &&
            !character_->oldControls.test(jumpControl) &&
            character_->tools.test(ironFanTool) && character_->airJumpCount)
        {
            return boost::shared_ptr<State>(new CharacterAirJumpState(character_, game_));
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

    void CharacterFallState::update(float dt)
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

    void CharacterFallState::exit()
    { }
}
