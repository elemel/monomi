#ifndef MONOMI_COLLISION_BODY_FWD_HPP
#define MONOMI_COLLISION_BODY_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class CollisionBody;
    
    typedef boost::shared_ptr<CollisionBody> CollisionBodyPtr;
    typedef boost::weak_ptr<CollisionBody> CollisionBodyWeakPtr;
}

#endif // MONOMI_COLLISION_BODY_FWD_HPP
