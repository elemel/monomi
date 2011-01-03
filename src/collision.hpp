#ifndef MONOMI_COLLISION_HPP
#define MONOMI_COLLISION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class CollisionShape;

    class Collision {
    public:
        boost::shared_ptr<CollisionShape> shape1() const;
        boost::shared_ptr<CollisionShape> shape2() const;
    };
}

#endif // MONOMI_COLLISION_HPP
