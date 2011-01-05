#ifndef MONOMI_COLLISION_DETECTOR_HPP
#define MONOMI_COLLISION_DETECTOR_HPP

#include <vector>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class CollisionBody;
    class CollisionShape;

    class CollisionDetector {
    public:
        typedef boost::shared_ptr<CollisionBody> BodyPtr;
        typedef std::vector<BodyPtr> BodyVector;
        typedef boost::shared_ptr<CollisionShape> ShapePtr;
        typedef std::pair<ShapePtr, ShapePtr> Collision;
        typedef std::vector<Collision> CollisionVector;

        void addBody(BodyPtr const &body);
        void removeBody(BodyPtr const &body);
        BodyVector const &bodies() const;

        CollisionVector const &collisions() const;

        void update(float dt);

    private:
        friend class CollisionBody;

        typedef std::vector<CollisionBody *> BodyRawVector;

        BodyVector bodies_;
        BodyRawVector dirtyBodies_;
        CollisionVector collisions_;

        void detectCollisions();
        void detectBodyCollision(CollisionBody const *body1,
                                 CollisionBody const *body2);
        void detectShapeCollision(ShapePtr const &shape1,
                                  ShapePtr const &shape2);

        void clearDirty();
    };
}

#endif // MONOMI_COLLISION_DETECTOR_HPP
