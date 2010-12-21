#include "character_state_component.hpp"

#include "character_actor.hpp"
#include "character_type.hpp"

#include <cmath>

namespace monomi {
    CharacterStateComponent::CharacterStateComponent(CharacterActor *character, Game *game) :
        character_(character),
        game_(game)
    { }

    void CharacterStateComponent::update(float dt)
    {
        // TODO: Extract separate states.
        if (character_->alive_) {
            if (character_->touchDown) {
                if (character_->techniques.test(tripleJumpTechnique)) {
                    character_->airJumpCount = 2;
                } else if (character_->techniques.test(doubleJumpTechnique)) {
                    character_->airJumpCount = 1;
                } else {
                    character_->airJumpCount = 0;
                }
            } else if (character_->wallSliding()) {
                character_->airJumpCount = 0;
            }
            if (character_->controls.test(jumpControl) && !character_->oldControls.test(jumpControl)) {
                if (character_->touchDown) {
                    character_->velocity.y = character_->type->jumpVelocity;
                } else if (character_->wallSliding()) {
                    if (character_->techniques.test(wallJumpTechnique)) {
                        int jumpFace = int(character_->touchLeft) - int(character_->touchRight);
                        if (jumpFace) {
                            character_->face = jumpFace;
                        }
                        character_->velocity.x = float(jumpFace) * character_->type->wallJumpVelocity.x;
                        character_->velocity.y = character_->type->wallJumpVelocity.y;
                    }
                } else {
                    if (character_->tools.test(ironFanTool) && character_->airJumpCount) {
                        --character_->airJumpCount;
                        character_->velocity.y = character_->type->airJumpVelocity;
                    }
                }
            }
            int moveFace = (int(character_->controls.test(rightControl)) -
                            int(character_->controls.test(leftControl)));
            if (moveFace) {
                character_->face = moveFace;
            }
            if (character_->touchDown) {
                if (moveFace) {
                    character_->velocity.x += (float(moveFace) * character_->type->walkAcceleration * dt);
                    character_->velocity.x = (sign(character_->velocity.x) *
                                              std::min(std::abs(character_->velocity.x),
                                                       character_->type->maxWalkVelocity));
                } else {
                    character_->velocity.x = (sign(character_->velocity.x) *
                                              std::max(std::abs(character_->velocity.x) -
                                                       character_->type->walkAcceleration * dt, 0.0f));
                }
            } else {
                if (moveFace) {
                    float driftVelocity = (character_->velocity.x + float(moveFace) *
                                           character_->type->driftAcceleration * dt);
                    character_->velocity.x = (sign(driftVelocity) *
                                              std::min(std::abs(driftVelocity),
                                                       std::max(std::abs(character_->velocity.x),
                                                                character_->type->maxDriftVelocity)));
                }
            }
            if (!character_->controls.test(jumpControl)) {
                character_->velocity.y = std::min(character_->velocity.y, 3.0f);
            }
        }

        // Copy controls.
        character_->oldControls = character_->controls;
    }
}
