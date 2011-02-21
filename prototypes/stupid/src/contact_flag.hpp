#ifndef MONOMI_CONTACT_FLAG_HPP
#define MONOMI_CONTACT_FLAG_HPP

#include <iostream>

namespace monomi {
    enum ContactFlag {
        UP_CONTACT,
        LEFT_CONTACT,
        DOWN_CONTACT,
        RIGHT_CONTACT,
        
        CONTACT_COUNT
    };

    std::ostream &operator<<(std::ostream &out, ContactFlag contact);
}

#endif // MONOMI_CONTACT_FLAG_HPP
