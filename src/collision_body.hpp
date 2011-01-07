#ifndef MONOMI_COLLISION_BODY_HPP
#define MONOMI_COLLISION_BODY_HPP

#include "collision_body_fwd.hpp"

#include "actor_fwd.hpp"
#include "collision_detector_fwd.hpp"
#include "collision_shape_fwd.hpp"
#include "geometry.hpp"

#include <complex>
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

        float rotation() const;
        void rotation(float rotation);

    private:
        friend class CollisionDetector;
        friend class CollisionShape;

        class TransformVisitor;

        ActorWeakPtr actor_;
        CollisionDetectorWeakPtr detector_;
        bool dirty_;
        ShapeVector shapes_;

        Vector2 translation_;
        float rotation_;
        std::complex<float> rotationComplex_;

        void dirty();
        void update();
    };
}

#endif // MONOMI_COLLISION_SHAPE_HPP
