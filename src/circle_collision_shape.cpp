#include "circle_collision_shape.hpp"

namespace monomi {
    CircleCollisionShape::CircleCollisionShape(ActorPtr const &actor,
                                               Circle2 const &circle) :
        actor_(actor),
        circle_(circle)
    { }

    ActorPtr CircleCollisionShape::actor() const
    {
        return actor_.lock();
    }

    Box2 CircleCollisionShape::boundingBox() const
    {
        return Box2();
    }

    Circle2 const &CircleCollisionShape::circle() const
    {
        return circle_;
    }

    void CircleCollisionShape::circle(Circle2 const &circle)
    {
        circle_ = circle;
    }
}
