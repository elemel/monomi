#ifndef MONOMI_COLLISION_BODY_HPP
#define MONOMI_COLLISION_BODY_HPP

#include "collision_body_fwd.hpp"

#include "actor_fwd.hpp"
#include "collision_detector_fwd.hpp"
#include "collision_shape_fwd.hpp"
#include "geometry.hpp"

#include <vector>
#include <boost/enable_shared_from_this.hpp>

namespace monomi {
    class CollisionBody :
        public boost::enable_shared_from_this<CollisionBody>
    {
    public:
        typedef std::vector<CollisionShapePtr> ShapeVector;
 
        explicit CollisionBody(ActorPtr const &actor);

        ActorPtr actor() const;

        void addShape(CollisionShapePtr const &shape);
        void removeShape(CollisionShapePtr const &shape);
        ShapeVector const &shapes() const;

        Vector2 const &translation() const;
        void translation(Vector2 const &translation);

    private:
        friend class CollisionDetector;
        friend class CollisionShape;

        ActorWeakPtr actor_;
        CollisionDetectorWeakPtr detector_;
        Vector2 translation_;
        bool dirty_;
        ShapeVector shapes_;

        void makeDirty();
    };
}

#endif // MONOMI_COLLISION_SHAPE_HPP
