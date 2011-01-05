#ifndef MONOMI_COLLISION_SHAPE_HPP
#define MONOMI_COLLISION_SHAPE_HPP

#include "collision_shape_fwd.hpp"

#include "actor_fwd.hpp"
#include "collision_body_fwd.hpp"
#include "geometry.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

namespace monomi {
    class CollisionShape {
    public:
        typedef boost::shared_ptr<CollisionBody> BodyPtr;
        typedef boost::variant<Box2, Circle> Shape;

        explicit CollisionShape(Shape const &shape = Shape());

        BodyPtr body() const;

        Shape const &shape() const;
        void shape(Shape const &shape);

    private:
        friend class CollisionBody;

        CollisionBodyWeakPtr body_;
        Shape shape_;

        void makeDirty();
    };
}

#endif // MONOMI_COLLISION_SHAPE_HPP
