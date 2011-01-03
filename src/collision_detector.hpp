#ifndef MONOMI_COLLISION_DETECTOR_HPP
#define MONOMI_COLLISION_DETECTOR_HPP

#include <vector>
#include <boost/signals2.hpp>

namespace monomi {
    class Collision;
    class CollisionShape;

    class CollisionDetector {
    public:
        typedef boost::shared_ptr<CollisionShape> ShapePtr;
        typedef std::vector<ShapePtr> ShapeVector;

        typedef boost::shared_ptr<Collision> CollisionPtr;
        typedef std::vector<CollisionPtr> CollisionVector;

        void addShape(ShapePtr const &shape);
        void updateShape(ShapePtr const &shape);
        void removeShape(ShapePtr const &shape);
        ShapeVector const &shapes() const;

        void updateCollisions();
        CollisionVector const &collisions() const;

    private:
        ShapeVector shapes_;
        CollisionVector collisions_;
    };
}

#endif // MONOMI_COLLISION_DETECTOR_HPP
