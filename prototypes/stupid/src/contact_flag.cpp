#include "contact_flag.hpp"

namespace monomi {
    std::ostream &operator<<(std::ostream &out, ContactFlag contact)
    {
        switch (contact) {
        case LEFT_CONTACT:
            return out << "left";

        case RIGHT_CONTACT:
            return out << "right";

        case DOWN_CONTACT:
            return out << "down";

        case UP_CONTACT:
            return out << "up";

        default:
            return out;
        }
    }
}
