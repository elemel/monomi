#ifndef MONOMI_COLLISION_CATEGORY_HPP
#define MONOMI_COLLISION_CATEGORY_HPP

namespace monomi {
    enum CollisionCategory {
        defaultCollisionCategory,

        platformCollisionCategory,
        shadowCollisionCategory,
        waterCollisionCategory,

        friendCollisionCategory,
        neutralCollisionCategory,
        enemyCollisionCategory,

        collisionCategoryCount
    };
}

#endif // MONOMI_COLLISION_CATEGORY_HPP
