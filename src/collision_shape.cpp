#include "collision_shape.hpp"

#include "collision_body.hpp"

namespace monomi {
    CollisionShape::CollisionShape() :
        body_(0)
    { }

    CollisionShape::BodyPtr CollisionShape::body() const
    {
        return body_ ? body_->shared_from_this() : BodyPtr();
    }

    ActorPtr CollisionShape::actor() const
    {
        return body_ ? body_->actor() : ActorPtr();
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
        if (body_) {
            body_->makeDirty();
        }
    }
}
