#ifndef MONOMI_CONTACT_FLAG_HPP
#define MONOMI_CONTACT_FLAG_HPP

#include <iostream>

namespace monomi {
    enum ContactFlag {
        UP_CONTACT_FLAG,
        LEFT_CONTACT_FLAG,
        DOWN_CONTACT_FLAG,
        RIGHT_CONTACT_FLAG,
        
        CONTACT_FLAG_COUNT
    };

    std::ostream &operator<<(std::ostream &out, ContactFlag contact);
}

#endif // MONOMI_CONTACT_FLAG_HPP
