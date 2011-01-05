#include "collision_body.hpp"
#include "collision_detector.hpp"

namespace monomi {
    CollisionBody::CollisionBody(ActorPtr const &actor) :
        actor_(actor),
        detector_(0),
        dirty_(false)
    { }

    ActorPtr CollisionBody::actor() const
    {
        return actor_.lock();
    }

    void CollisionBody::addShape(ShapePtr const &shape)
    {
        assert(shape->body_.lock() == 0);
    }

    void CollisionBody::removeShape(ShapePtr const &shape)
    {
        assert(shape->body_.lock() == this);
    }

    CollisionBody::ShapeVector const &CollisionBody::shapes() const
    {
        return shapes_;
    }

    Vector2 const &CollisionBody::translation() const
    {
        return translation_;
    }

    void CollisionBody::translation(Vector2 const &translation)
    {
        translation_ = translation;
        makeDirty();
    }

    void CollisionBody::makeDirty()
    {
        if (detector_ && !dirty_) {
            dirty_ = true;
            detector_->dirtyBodies_.push_back(this);
        }
    }
}
