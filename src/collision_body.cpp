#include "collision_body.hpp"

#include "collision_detector.hpp"
#include "collision_shape.hpp"

namespace monomi {
    CollisionBody::CollisionBody(ActorPtr const &actor) :
        actor_(actor),
        dirty_(false),
        rotation_(0.0f),
        rotationComplex_(std::polar(1.0f, 0.0f))
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
        dirty();
    }

    void CollisionBody::removeShape(CollisionShapePtr const &shape)
    {
        assert(shape->body_.lock().get() == this);
        shape->body_.reset();
        shapes_.erase(std::find(shapes_.begin(), shapes_.end(), shape));
        dirty();
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
        dirty();
    }

    float CollisionBody::rotation() const
    {
        return rotation_;
    }

    void CollisionBody::rotation(float rotation)
    {
        rotation_ = rotation;
        dirty();
    }

    void CollisionBody::dirty()
    {
        if (!dirty_) {
            dirty_ = true;
            if (CollisionDetectorPtr detector = detector_.lock()) {
                detector->dirtyBodies_.push_back(this->shared_from_this());
            }
        }
    }

    class CollisionBody::TransformVisitor {
    public:
        typedef CollisionShape::Shape result_type;

        Vector2 translation;
        std::complex<float> rotation;

        TransformVisitor(Vector2 translation,
                         std::complex<float> const &rotation)
        :
            translation(translation),
            rotation(rotation)
        { }

        CollisionShape::Shape operator()(Box2 const &box) const
        {
            return Box2(translation + box.p1, translation + box.p2);
        }

        CollisionShape::Shape operator()(Circle const &circle) const
        {
            return Circle(translation + circle.center, circle.radius);
        }
    };

    void CollisionBody::update()
    {
        rotationComplex_ = std::polar(1.0f, rotation_);
        TransformVisitor visitor(translation_, rotationComplex_);
        for (ShapeVector::iterator i = shapes_.begin(); i != shapes_.end();
             ++i)
        {
            (*i)->worldShape_ = boost::apply_visitor(visitor, (*i)->shape_);
        }
    }
}
