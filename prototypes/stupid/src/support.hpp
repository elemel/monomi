#ifndef MONOMI_SUPPORT_HPP
#define MONOMI_SUPPORT_HPP

#include <iostream>

namespace monomi {
    enum Support {
        UP_SUPPORT,
        LEFT_SUPPORT,
        DOWN_SUPPORT,
        RIGHT_SUPPORT,
        
        SUPPORT_COUNT
    };

    std::ostream &operator<<(std::ostream &out, Support support);
}

#endif // MONOMI_SUPPORT_HPP
