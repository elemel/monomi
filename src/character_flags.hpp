#ifndef MONOMI_CHARACTER_FLAGS_HPP
#define MONOMI_CHARACTER_FLAGS_HPP

#include <bitset>

namespace monomi {
    enum CharacterControlFlag {
        CHARACTER_UP_CONTROL,
        CHARACTER_LEFT_CONTROL,
        CHARACTER_DOWN_CONTROL,
        CHARACTER_RIGHT_CONTROL,

        CHARACTER_RUN_CONTROL,
        CHARACTER_JUMP_CONTROL,
        CHARACTER_ACTION_CONTROL,

        CHARACTER_CONTROL_COUNT
    };

    typedef std::bitset<CHARACTER_CONTROL_COUNT> CharacterControlSet;

    enum CharacterSensorFlag {
        CHARACTER_CEILING_SENSOR,
        CHARACTER_LEFT_WALL_SENSOR,
        CHARACTER_RIGHT_WALL_SENSOR,
        CHARACTER_FLOOR_SENSOR,

        CHARACTER_SENSOR_COUNT
    };

    typedef std::bitset<CHARACTER_SENSOR_COUNT> CharacterSensorSet;

    std::ostream &operator<<(std::ostream &out, CharacterSensorFlag sensor);

    enum CharacterTechniqueFlag {
        CHARACTER_CEILING_RUN_TECHNIQUE,
        CHARACTER_DOUBLE_JUMP_TECHNIQUE,
        CHARACTER_GLIDE_TECHNIQUE,
        CHARACTER_SLIDE_TECHNIQUE,
        CHARACTER_STOMP_TECHNIQUE,
        CHARACTER_TELEPORT_TECHNIQUE,
        CHARACTER_TRIPLE_JUMP_TECHNIQUE,
        CHARACTER_WALL_JUMP_TECHNIQUE,
        CHARACTER_WALL_RUN_TECHNIQUE,
        CHARACTER_WALL_SLIDE_TECHNIQUE,

        CHARACTER_TECHNIQUE_COUNT
    };

    typedef std::bitset<CHARACTER_TECHNIQUE_COUNT> CharacterTechniqueSet;

    enum CharacterToolFlag {
        CHARACTER_AIR_SKIN_TOOL,
        CHARACTER_BAMBOO_FLUTE_TOOL,
        CHARACTER_GRAPPLING_HOOK_TOOL,
        CHARACTER_IRON_FAN_TOOL,
        CHARACTER_SMOKE_BOMBS_TOOL,
        CHARACTER_STRAW_BASKET_TOOL,
        CHARACTER_THROWING_STARS_TOOL,
        CHARACTER_TIGER_CLAWS_TOOL,

        CHARACTER_TOOL_COUNT
    };

    typedef std::bitset<CHARACTER_TOOL_COUNT> CharacterToolSet;
}

#endif // MONOMI_CHARACTER_FLAGS_HPP