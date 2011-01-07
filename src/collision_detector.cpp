#include "collision_detector.hpp"

#include "collision_body.hpp"
#include "collision_shape.hpp"
#include "debug_graphics.hpp"

#include <algorithm>

namespace monomi {
    class CollisionDetector::DebugDrawVisitor {
    public:
        typedef void result_type;

        DebugGraphicsPtr graphics;

        explicit DebugDrawVisitor(DebugGraphicsPtr const &graphics) :
            graphics(graphics)
        { }

        template <typename T>
        void operator()(T const &shape) const
        {
            graphics->draw(shape);
        }
    };

    class CollisionDetector::IntersectsVisitor {
    public:
        typedef bool result_type;

        template <typename T, typename U>
        bool operator()(T const &s1, U const &s2) const
        {
            return intersects(s1, s2);
        }
    };

    void CollisionDetector::addBody(CollisionBodyPtr const &body)
    {
        assert(body->detector_.lock().empty());
        assert(!body->dirty_);
        body->detector_ = this->shared_from_this();
        bodies_.push_back(body);
        body->dirty_ = true;
        dirtyBodies_.push_back(body);
    }

    void CollisionDetector::removeBody(CollisionBodyPtr const &body)
    {
        assert(body->detector_.lock().get() == this);
        body->detector_.reset();
        bodies_.erase(std::find(bodies_.begin(), bodies_.end(), body));
        if (body->dirty_) {
            body->dirty_ = false;
            dirtyBodies_.erase(std::find(dirtyBodies_.begin(),
                                         dirtyBodies_.end(), body));
        }
    }

    CollisionDetector::BodyVector const &CollisionDetector::bodies() const
    {
        return bodies_;
    }

    CollisionDetector::CollisionVector const &
    CollisionDetector::collisions() const
    {
        return collisions_;
    }

    void CollisionDetector::update(float dt)
    {
        updateCollisions();
        clearDirtyBodies();
    }

    void CollisionDetector::debugDraw(DebugGraphicsPtr const &graphics) const
    {
        DebugDrawVisitor visitor(graphics);
        for (BodyVector::const_iterator i = bodies_.begin();
             i != bodies_.end(); ++i)
        {
            CollisionBody::ShapeVector const &shapes = (*i)->shapes();
            for (CollisionBody::ShapeVector::const_iterator j =
                 shapes.begin(); j != shapes.end(); ++j)
            {
                boost::apply_visitor(visitor, (*j)->worldShape_);
            }
        }
    }

    void CollisionDetector::updateDirtyBodies()
    {
        for (BodyVector::iterator i = dirtyBodies_.begin();
             i != dirtyBodies_.end(); ++i)
        {
            (*i)->update();
        }
    }

    void CollisionDetector::updateCollisions()
    {
        collisions_.clear();
        for (BodyVector::iterator i = dirtyBodies_.begin();
             i != dirtyBodies_.end(); ++i)
        {
            for (BodyVector::iterator j = bodies_.begin(); j != bodies_.end();
                 ++j)
            {
                detectBodyCollision(*i, *j);
            }
        }
    }

    void CollisionDetector::detectBodyCollision(CollisionBodyPtr const body1,
                                                CollisionBodyPtr const body2)
    {
        if (!body2->dirty_ || body1 < body2) {
            CollisionBody::ShapeVector const &shapes1 = body1->shapes();
            CollisionBody::ShapeVector const &shapes2 = body2->shapes();

            typedef CollisionBody::ShapeVector::const_iterator Iterator;
            for (Iterator i = shapes1.begin(); i != shapes1.end(); ++i) {
                for (Iterator j = shapes2.begin(); j != shapes2.end(); ++j) {
                    detectShapeCollision(*i, *j);
                }
            }
        }
    }

    void
    CollisionDetector::detectShapeCollision(CollisionShapePtr const &shape1,
                                            CollisionShapePtr const &shape2)
    {
        if (boost::apply_visitor(IntersectsVisitor(), shape1->worldShape_,
            shape2->worldShape_))
        {
            collisions_.push_back(Collision(shape1, shape2));
        }
    }

    void CollisionDetector::clearDirtyBodies()
    {
        for (BodyVector::iterator i = dirtyBodies_.begin();
             i != dirtyBodies_.end(); ++i)
        {
            (*i)->dirty_ = false;
        }
        dirtyBodies_.clear();
    }
}
