#ifndef MONOMI_CHARACTER_SENSOR_FLAG_HPP
#define MONOMI_CHARACTER_SENSOR_FLAG_HPP

#include <bitset>

namespace monomi {
    enum CharacterSensorFlag {
        CHARACTER_CEILING_SENSOR,
        CHARACTER_LEFT_WALL_SENSOR,
        CHARACTER_RIGHT_WALL_SENSOR,
        CHARACTER_FLOOR_SENSOR,

        CHARACTER_SENSOR_COUNT
    };

    typedef std::bitset<CHARACTER_SENSOR_COUNT> CharacterSensorFlagSet;

    std::ostream &operator<<(std::ostream &out, CharacterSensorFlag sensor);
}

#endif // MONOMI_CHARACTER_SENSOR_FLAG_HPP
