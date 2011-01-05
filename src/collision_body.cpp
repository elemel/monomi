#include "collision_body.hpp"

#include "collision_detector.hpp"
#include "collision_shape.hpp"

namespace monomi {
    CollisionBody::CollisionBody(ActorPtr const &actor) :
        actor_(actor),
        detector_(0),
        dirty_(false)
    { }

    CollisionBody::~CollisionBody()
    {
        for (ShapeVector::iterator i = shapes_.begin(); i != shapes_.end();
             ++i)
        {
            (*i)->body_ = 0;
        }
    }

    ActorPtr CollisionBody::actor() const
    {
        return actor_.lock();
    }

    void CollisionBody::addShape(ShapePtr const &shape)
    {
        assert(shape->body_ == 0);
        shape->body_ = this;
        shapes_.push_back(shape);
        makeDirty();
    }

    void CollisionBody::removeShape(ShapePtr const &shape)
    {
        assert(shape->body_ == this);
        shape->body_ = 0;
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
        if (detector_ && !dirty_) {
            dirty_ = true;
            detector_->dirtyBodies_.push_back(this);
        }
    }
}
