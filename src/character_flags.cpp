#include "character_flags.hpp"

namespace monomi {
    std::ostream &operator<<(std::ostream &out, CharacterSensorFlag flag)
    {
        switch (flag) {
        case CHARACTER_CEILING_SENSOR:
            return out << "ceiling";

        case CHARACTER_LEFT_WALL_SENSOR:
            return out << "left-wall";

        case CHARACTER_FLOOR_SENSOR:
            return out << "floor";

        case CHARACTER_RIGHT_WALL_SENSOR:
            return out << "right-wall";

        default:
            return out;
        }
    }
}
