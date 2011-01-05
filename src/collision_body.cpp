#include "collision_body.hpp"

#include "collision_detector.hpp"
#include "collision_shape.hpp"

namespace monomi {
    CollisionBody::CollisionBody(ActorPtr const &actor) :
        actor_(actor),
        dirty_(false)
    { }

    ActorPtr CollisionBody::actor() const
    {
        return actor_.lock();
    }

    void CollisionBody::addShape(CollisionShapePtr const &shape)
    {
        assert(shape->body_.lock().empty());
        shape->body_ = this->shared_from_this();
        shapes_.push_back(shape);
        makeDirty();
    }

    void CollisionBody::removeShape(CollisionShapePtr const &shape)
    {
        assert(shape->body_.lock().get() == this);
        shape->body_.reset();
        shapes_.erase(std::find(shapes_.begin(), shapes_.end(), shape));
        makeDirty();
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
        if (!dirty_) {
            dirty_ = true;
            if (CollisionDetectorPtr detector = detector_.lock()) {
                detector->dirtyBodies_.push_back(this);
            }
        }
    }
}
