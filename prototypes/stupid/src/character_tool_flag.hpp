#ifndef MONOMI_CHARACTER_TOOL_FLAG_HPP
#define MONOMI_CHARACTER_TOOL_FLAG_HPP

#include <bitset>

namespace monomi {
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

    typedef std::bitset<CHARACTER_TOOL_COUNT> CharacterToolFlagSet;
}

#endif // MONOMI_CHARACTER_TOOL_FLAG_HPP
