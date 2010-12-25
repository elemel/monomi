#include "character_walk_state.hpp"

#include "character_actor.hpp"
#include "character_fall_state.hpp"
#include "character_jump_state.hpp"
#include "character_type.hpp"

#include <cmath>

namespace monomi {
    CharacterWalkState::CharacterWalkState(CharacterActor *character, Game *game) :
        character_(character),
        game_(game)
    { }    

    void CharacterWalkState::enter()
    {
        if (character_->techniques.test(tripleJumpTechnique)) {
            character_->airJumpCount = 2;
        } else if (character_->techniques.test(doubleJumpTechnique)) {
            character_->airJumpCount = 1;
        } else {
            character_->airJumpCount = 0;
        }
    }

    boost::shared_ptr<State> CharacterWalkState::transition()
    {
        if (character_->inputs.test(jumpInput) && !character_->oldInputs.test(jumpInput)) {
            return boost::shared_ptr<State>(new CharacterJumpState(character_, game_));
        } else if (!character_->contacts.test(downContact)) {
            return boost::shared_ptr<State>(new CharacterFallState(character_, game_));
        } else {
            return boost::shared_ptr<State>();
        }
    }

    void CharacterWalkState::update(float dt)
    {
        int moveFace = (int(character_->inputs.test(rightInput)) -
                        int(character_->inputs.test(leftInput)));
        if (moveFace) {
            character_->face = moveFace;
        }
        if (moveFace) {
            character_->velocity.x += (float(moveFace) * character_->type()->walkAcceleration * dt);
            character_->velocity.x = (sign(character_->velocity.x) *
                                      std::min(std::abs(character_->velocity.x),
                                               character_->type()->maxWalkVelocity));
        } else {
            character_->velocity.x = (sign(character_->velocity.x) *
                                      std::max(std::abs(character_->velocity.x) -
                                               character_->type()->walkAcceleration * dt, 0.0f));
        }
    }

    void CharacterWalkState::exit()
    { }
}
