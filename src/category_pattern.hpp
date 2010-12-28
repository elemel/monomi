#ifndef MONOMI_CATEGORY_PATTERN_HPP
#define MONOMI_CATEGORY_PATTERN_HPP

#include "category.hpp"

#include <bitset>

namespace monomi {
    class CategoryPattern {
    public:
        typedef std::bitset<categoryCount> CategoryBits;

        CategoryBits categories;
        CategoryBits includeCategories;
        CategoryBits excludeCategories;

        explicit CategoryPattern(CategoryBits const &categories = 0ul,
                                 CategoryBits const &includeCategories = ~0ul,
                                 CategoryBits const &excludeCategories = 0ul);
    };

    bool matches(CategoryPattern const &p1, CategoryPattern const &p2);
}

#endif // MONOMI_PATTERN_HPP
