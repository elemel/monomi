#include "collision_detector.hpp"

#include <algorithm>

namespace monomi {
    void CollisionDetector::addShape(ShapePtr const &shape)
    {
        assert(std::find(shapes_.begin(), shapes_.end(), shape) == shapes_.end());
        shapes_.push_back(shape);
    }

    void CollisionDetector::updateShape(ShapePtr const &shape)
    {
        
    }

    void CollisionDetector::removeShape(ShapePtr const &shape)
    {
        ShapeVector::iterator i = std::find(shapes_.begin(), shapes_.end(), shape);
        assert(i != shapes_.end());
        shapes_.erase(i);
    }

    CollisionDetector::ShapeVector const &CollisionDetector::shapes() const
    {
        return shapes_;
    }

    CollisionDetector::CollisionVector const &CollisionDetector::collisions() const
    {
        return collisions_;
    }

    void CollisionDetector::updateCollisions()
    {
    }
}
