#ifndef MONOMI_COLLISION_SHAPE_HPP
#define MONOMI_COLLISION_SHAPE_HPP

#include "geometry.hpp"

#include <boost/variant.hpp>

namespace monomi {
    class CollisionBody;

    class CollisionShape {
    public:
        typedef boost::variant<Box2, Circle> Shape;

        CollisionShape();

        CollisionBody *body() const;

        Shape const &shape() const;
        void shape(Shape const &shape);

    private:
        friend class CollisionBody;

        CollisionBody *body_;
        Shape shape_;

        void makeDirty();
    };
}

#endif // MONOMI_COLLISION_SHAPE_HPP
