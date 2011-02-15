#ifndef MONOMI_SUPPORT_FLAG_HPP
#define MONOMI_SUPPORT_FLAG_HPP

#include <iostream>

namespace monomi {
    enum SupportFlag {
        UP_SUPPORT_FLAG,
        LEFT_SUPPORT_FLAG,
        DOWN_SUPPORT_FLAG,
        RIGHT_SUPPORT_FLAG,
        
        SUPPORT_FLAG_COUNT
    };

    std::ostream &operator<<(std::ostream &out, SupportFlag support);
}

#endif // MONOMI_SUPPORT_FLAG_HPP
