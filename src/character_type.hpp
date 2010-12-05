#ifndef MONOMI_CHARACTER_TYPE_HPP
#define MONOMI_CHARACTER_TYPE_HPP

#include "geometry.hpp"
#include "technique.hpp"
#include "tool.hpp"

#include <bitset>

namespace monomi {
    class CharacterType {
    public:
        float radius;
        float maxVelocity;
        float walkAcceleration;
        float maxWalkVelocity;
        float driftAcceleration;
        float maxDriftVelocity;
        float jumpVelocity;
        Vector2 wallJumpVelocity;
        float airJumpVelocity;
        std::bitset<techniqueCount> techniques;
        std::bitset<toolCount> tools;

        CharacterType();
    };
}

#endif // MONOMI_CHARACTER_TYPE_HPP
