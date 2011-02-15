#ifndef MONOMI_CATEGORY_FLAG_HPP
#define MONOMI_CATEGORY_FLAG_HPP

namespace monomi {
    // Collision categories.
    enum CategoryFlag {
        DEFAULT_CATEGORY_FLAG,

        PLATFORM_CATEGORY_FLAG,
        SHADOW_CATEGORY_FLAG,
        WATER_CATEGORY_FLAG,

        FRIEND_CATEGORY_FLAG,
        NEUTRAL_CATEGORY_FLAG,
        ENEMY_CATEGORY_FLAG,

        CATEGORY_FLAG_COUNT
    };
}

#endif // MONOMI_CATEGORY_FLAG_HPP
