#ifndef MONOMI_CIRCLE_COLLISION_SHAPE_HPP
#define MONOMI_CIRCLE_COLLISION_SHAPE_HPP

#include "collision_shape.hpp"

namespace monomi {
    class CircleCollisionShape :
        public CollisionShape
    {
    public:
        explicit CircleCollisionShape(ActorPtr const &actor,
                                      Circle2 const &circle = Circle());

        ActorPtr actor() const;
        Box2 boundingBox() const;

        Circle2 const &circle() const;
        void circle(Circle2 const &circle);

    private:
        ActorWeakPtr actor_;
        Circle2 circle_;
    };
}

#endif // MONOMI_CIRCLE_COLLISION_SHAPE_HPP
