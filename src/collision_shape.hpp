#ifndef MONOMI_COLLISION_SHAPE_HPP
#define MONOMI_COLLISION_SHAPE_HPP

#include "actor_fwd.hpp"

#include <boost/shared_ptr.hpp>

namespace monomi {
    class Box2;

    class CollisionShape {
    public:
        virtual ~CollisionShape()
        { }

        virtual ActorPtr actor() const = 0;
        virtual Box2 boundingBox() const = 0;
    };
}

#endif // MONOMI_COLLISION_SHAPE_HPP
