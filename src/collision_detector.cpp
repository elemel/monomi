#include "collision_detector.hpp"

#include "collision_body.hpp"

#include <algorithm>

namespace monomi {
    void CollisionDetector::addBody(BodyPtr const &body)
    {
        assert(body->detector_ == 0);
        assert(!body->dirty_);
        body->detector_ = this;
        bodies_.push_back(body);
        body->dirty_ = true;
        dirtyBodies_.push_back(body.get());
    }

    void CollisionDetector::removeBody(BodyPtr const &body)
    {
        assert(body->detector_ == this);
        body->detector_ = 0;
        bodies_.erase(std::find(bodies_.begin(), bodies_.end(), body));
        if (body->dirty_) {
            body->dirty_ = false;
            dirtyBodies_.erase(std::find(dirtyBodies_.begin(),
                                         dirtyBodies_.end(), body.get()));
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
        collisions_.clear();
        detectCollisions();
        clearDirty();
    }

    void CollisionDetector::detectCollisions()
    {
        for (BodyRawVector::iterator i = dirtyBodies_.begin();
             i != dirtyBodies_.end(); ++i)
        {
            for (BodyVector::iterator j = bodies_.begin(); j != bodies_.end();
                 ++j)
            {
                detectBodyCollision(*i, j->get());
            }
        }
    }

    void CollisionDetector::detectBodyCollision(CollisionBody const *body1,
                                                CollisionBody const *body2)
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

    void CollisionDetector::detectShapeCollision(ShapePtr const &shape1,
                                                 ShapePtr const &shape2)
    { }

    void CollisionDetector::clearDirty()
    {
        for (BodyRawVector::iterator i = dirtyBodies_.begin();
             i != dirtyBodies_.end(); ++i)
        {
            (*i)->dirty_ = false;
        }
        dirtyBodies_.clear();
    }
}
