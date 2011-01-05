#ifndef MONOMI_COLLISION_SHAPE_HPP
#define MONOMI_COLLISION_SHAPE_HPP

#include "actor_fwd.hpp"
#include "geometry.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

namespace monomi {
    class CollisionBody;

    class CollisionShape {
    public:
        typedef boost::shared_ptr<CollisionBody> BodyPtr;
        typedef boost::variant<Box2, Circle> Shape;

        CollisionShape();

        BodyPtr body() const;
        ActorPtr actor() const;

        Shape const &shape() const;
        void shape(Shape const &shape);

    private:
        friend class CollisionBody;

        CollisionBody *body_;
        Shape shape_;

        void makeDirty();
    };
}

#endif // MONOMI_COLLISION_SHAPE_HPP
