#include "collision_shape.hpp"

#include "collision_body.hpp"

namespace monomi {
    CollisionShape::CollisionShape(Shape const &shape) :
        shape_(shape)
    { }

    CollisionShape::BodyPtr CollisionShape::body() const
    {
        return body_.lock();
    }

    CollisionShape::Shape const &CollisionShape::shape() const
    {
        return shape_;
    }

    void CollisionShape::shape(Shape const &shape)
    {
        shape_ = shape;
        makeDirty();
    }

    void CollisionShape::makeDirty()
    {
        if (CollisionBodyPtr body = body_.lock()) {
            body->makeDirty();
        }
    }
}
