#include "support.hpp"

namespace monomi {
    std::ostream &operator<<(std::ostream &out, Support support)
    {
        switch (support) {
        case LEFT_SUPPORT:
            return out << "left";

        case RIGHT_SUPPORT:
            return out << "right";

        case DOWN_SUPPORT:
            return out << "down";

        case UP_SUPPORT:
            return out << "up";

        default:
            return out;
        }
    }
}
