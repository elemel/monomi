#include "category_pattern.hpp"

namespace monomi {
    CategoryPattern::CategoryPattern(CategoryBits const &categories,
                                     CategoryBits const &includeCategories,
                                     CategoryBits const &excludeCategories) :
        categories(categories),
        includeCategories(includeCategories),
        excludeCategories(excludeCategories)
    { }

    bool matches(CategoryPattern const &p1, CategoryPattern const &p2)
    {
        bool included = (p1.categories & p2.includeCategories |
                         p2.categories & p1.includeCategories).any();
        bool excluded = (p1.categories & p2.excludeCategories |
                         p2.categories & p1.excludeCategories).any();
        return included && !excluded;
    }
}
