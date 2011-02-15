#ifndef MONOMI_CATEGORY_FLAG_HPP
#define MONOMI_CATEGORY_FLAG_HPP

namespace monomi {
    // Collision categories.
    enum CategoryFlag {
        defaultCategoryFlag,

        platformCategoryFlag,
        shadowCategoryFlag,
        waterCategoryFlag,

        friendCategoryFlag,
        neutralCategoryFlag,
        enemyCategoryFlag,

        categoryFlagCount
    };
}

#endif // MONOMI_CATEGORY_FLAG_HPP
