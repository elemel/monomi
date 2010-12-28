#include "pattern.hpp"

namespace monomi {
    Pattern::Pattern(CategoryBits const &categories,
                     CategoryBits const &includeCategories,
                     CategoryBits const &excludeCategories) :
        categories(categories),
        includeCategories(includeCategories),
        excludeCategories(excludeCategories)
    { }

    bool matches(Pattern const &p1, Pattern const &p2)
    {
        bool included = (p1.categories & p2.includeCategories |
                         p2.categories & p1.includeCategories).any();
        bool excluded = (p1.categories & p2.excludeCategories |
                         p2.categories & p1.excludeCategories).any();
        return included && !excluded;
    }
}
