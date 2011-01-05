#ifndef MONOMI_COLLISION_DETECTOR_FWD_HPP
#define MONOMI_COLLISION_DETECTOR_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class CollisionDetector;
    
    typedef boost::shared_ptr<CollisionDetector> CollisionDetectorPtr;
    typedef boost::weak_ptr<CollisionDetector> CollisionDetectorWeakPtr;
}

#endif // MONOMI_COLLISION_DETECTOR_FWD_HPP
