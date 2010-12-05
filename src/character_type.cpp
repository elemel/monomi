#include "character_type.hpp"

namespace monomi {
    CharacterType::CharacterType() :
        radius(0.75f),
        maxVelocity(20.0f),
        walkAcceleration(12.0f),
        maxWalkVelocity(8.0f),
        driftAcceleration(10.0f),
        maxDriftVelocity(6.0f),
        jumpVelocity(12.0f),
        wallJumpVelocity(6.0f, 9.0f),
        airJumpVelocity(12.0f)
    { }
}
