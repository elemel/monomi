#ifndef MONOMI_COLLISION_BODY_HPP
#define MONOMI_COLLISION_BODY_HPP

#include "actor_fwd.hpp"
#include "geometry.hpp"

#include <vector>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class CollisionDetector;
    class CollisionShape;

    class CollisionBody :
        public boost::enable_shared_from_this<CollisionBody>
    {
    public:
        typedef boost::shared_ptr<CollisionShape> ShapePtr;
        typedef std::vector<ShapePtr> ShapeVector;
 
        explicit CollisionBody(ActorPtr const &actor);
        ~CollisionBody();

        ActorPtr actor() const;

        void addShape(ShapePtr const &shape);
        void removeShape(ShapePtr const &shape);
        ShapeVector const &shapes() const;

        Vector2 const &translation() const;
        void translation(Vector2 const &translation);

    private:
        friend class CollisionDetector;
        friend class CollisionShape;

        ActorWeakPtr actor_;
        CollisionDetector *detector_;
        Vector2 translation_;
        bool dirty_;
        ShapeVector shapes_;

        void makeDirty();
    };
}

#endif // MONOMI_COLLISION_SHAPE_HPP
