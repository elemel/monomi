#ifndef MONOMI_COLLISION_SHAPE_FWD_HPP
#define MONOMI_COLLISION_SHAPE_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class CollisionShape;
    
    typedef boost::shared_ptr<CollisionShape> CollisionShapePtr;
    typedef boost::weak_ptr<CollisionShape> CollisionShapeWeakPtr;
}

#endif // MONOMI_COLLISION_SHAPE_FWD_HPP
