#ifndef MONOMI_CHARACTER_CONTROL_FLAG_HPP
#define MONOMI_CHARACTER_CONTROL_FLAG_HPP

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

        typedef std::bitset<CHARACTER_CONTROL_COUNT> CharacterControlFlagSet;
}

#endif // MONOMI_CHARACTER_CONTROL_FLAG_HPP
