#include "support_flag.hpp"

namespace monomi {
    std::ostream &operator<<(std::ostream &out, SupportFlag support)
    {
        switch (support) {
        case LEFT_SUPPORT_FLAG:
            return out << "left";

        case RIGHT_SUPPORT_FLAG:
            return out << "right";

        case DOWN_SUPPORT_FLAG:
            return out << "down";

        case UP_SUPPORT_FLAG:
            return out << "up";

        default:
            return out;
        }
    }
}
