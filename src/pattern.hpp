#ifndef MONOMI_PATTERN_HPP
#define MONOMI_PATTERN_HPP

#include "category.hpp"

#include <bitset>

namespace monomi {
    class Pattern {
    public:
        typedef std::bitset<categoryCount> CategoryBits;

        CategoryBits categories;
        CategoryBits includeCategories;
        CategoryBits excludeCategories;

        explicit Pattern(CategoryBits const &categories = 0ul,
                         CategoryBits const &includeCategories = ~0ul,
                         CategoryBits const &excludeCategories = 0ul);
    };

    bool matches(Pattern const &p1, Pattern const &p2);
}

#endif // MONOMI_PATTERN_HPP
