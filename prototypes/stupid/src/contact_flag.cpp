#include "contact_flag.hpp"

namespace monomi {
    std::ostream &operator<<(std::ostream &out, ContactFlag contact)
    {
        switch (contact) {
        case LEFT_CONTACT_FLAG:
            return out << "left";

        case RIGHT_CONTACT_FLAG:
            return out << "right";

        case DOWN_CONTACT_FLAG:
            return out << "down";

        case UP_CONTACT_FLAG:
            return out << "up";

        default:
            return out;
        }
    }
}
