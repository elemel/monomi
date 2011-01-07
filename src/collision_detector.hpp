#ifndef MONOMI_COLLISION_DETECTOR_HPP
#define MONOMI_COLLISION_DETECTOR_HPP

#include "collision_detector_fwd.hpp"

#include "collision_body_fwd.hpp"
#include "collision_shape_fwd.hpp"
#include "debug_graphics_fwd.hpp"

#include <vector>
#include <boost/enable_shared_from_this.hpp>

namespace monomi {
    class CollisionDetector :
        public boost::enable_shared_from_this<CollisionDetector>
    {
    public:
        typedef std::vector<CollisionBodyPtr> BodyVector;
        typedef std::pair<CollisionShapePtr, CollisionShapePtr> Collision;
        typedef std::vector<Collision> CollisionVector;

        void addBody(CollisionBodyPtr const &body);
        void removeBody(CollisionBodyPtr const &body);
        BodyVector const &bodies() const;

        CollisionVector const &collisions() const;

        void update(float dt);

        void debugDraw(DebugGraphicsPtr const &graphics) const;

    private:
        friend class CollisionBody;

        class DebugDrawVisitor;
        class IntersectsVisitor;

        BodyVector bodies_;
        BodyVector dirtyBodies_;
        CollisionVector collisions_;

        void updateDirtyBodies();
        void updateCollisions();
        void detectBodyCollision(CollisionBodyPtr const body1,
                                 CollisionBodyPtr const body2);
        void detectShapeCollision(CollisionShapePtr const &shape1,
                                  CollisionShapePtr const &shape2);

        void clearDirtyBodies();
    };
}

#endif // MONOMI_COLLISION_DETECTOR_HPP
