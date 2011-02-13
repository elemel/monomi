#ifndef MONOMI_FORMAT_ENUM_BITS_HPP
#define MONOMI_FORMAT_ENUM_BITS_HPP

#include <bitset>
#include <iostream>

namespace monomi {
    template <typename E, std::size_t N>
    void formatEnumBits(std::ostream &out, std::bitset<N> const &bits) {
        std::size_t count = bits.count();
        if (count == 0) {
            out << "none";
        } else {
            std::size_t j = 0;
            for (std::size_t i = 0; i < N; ++i) {
                if (bits.test(i)) {
                    if (count == 2 && j == count - 1) {
                        out << " and ";
                    } else if (count >= 3 && j >= 1 && j < count - 1) {
                        out << ", ";
                    } else if (count >= 3 && j == count - 1) {
                        // Serial comma.
                        out << ", and ";
                    }
                    out << E(i);
                    ++j;
                }
            }
        }
    }
}

#endif // MONOMI_FORMAT_ENUM_BITS_HPP
