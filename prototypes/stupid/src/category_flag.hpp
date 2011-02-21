#ifndef MONOMI_CATEGORY_FLAG_HPP
#define MONOMI_CATEGORY_FLAG_HPP

namespace monomi {
    // Collision categories.
    enum CategoryFlag {
        DEFAULT_CATEGORY,

        PLATFORM_CATEGORY,
        SHADOW_CATEGORY,
        WATER_CATEGORY,

        FRIEND_CATEGORY,
        NEUTRAL_CATEGORY,
        ENEMY_CATEGORY,

        CATEGORY_COUNT
    };
}

#endif // MONOMI_CATEGORY_FLAG_HPP
