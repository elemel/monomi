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
        dirty();
    }

    void CollisionShape::dirty()
    {
        if (CollisionBodyPtr body = body_.lock()) {
            body->dirty();
        }
    }
}
