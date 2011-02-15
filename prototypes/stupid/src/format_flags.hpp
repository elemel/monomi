#ifndef MONOMI_FORMAT_FLAGS_HPP
#define MONOMI_FORMAT_FLAGS_HPP

#include <bitset>
#include <iostream>

namespace monomi {
    template <typename T, std::size_t N>
    void formatFlags(std::ostream &out, std::bitset<N> const &flags) {
        std::size_t count = flags.count();
        if (count == 0) {
            out << "none";
        } else {
            std::size_t j = 0;
            for (std::size_t i = 0; i < N; ++i) {
                if (flags.test(i)) {
                    if (count == 2 && j == count - 1) {
                        out << " and ";
                    } else if (count >= 3 && j >= 1 && j < count - 1) {
                        out << ", ";
                    } else if (count >= 3 && j == count - 1) {
                        // Serial comma.
                        out << ", and ";
                    }
                    out << T(i);
                    ++j;
                }
            }
        }
    }
}

#endif // MONOMI_FORMAT_FLAGS_HPP
