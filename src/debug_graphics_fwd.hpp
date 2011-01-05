#ifndef MONOMI_DEBUG_GRAPHICS_FWD_HPP
#define MONOMI_DEBUG_GRAPHICS_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class DebugGraphics;
    
    typedef boost::shared_ptr<DebugGraphics> DebugGraphicsPtr;
    typedef boost::weak_ptr<DebugGraphics> DebugGraphicsWeakPtr;
}

#endif // MONOMI_DEBUG_GRAPHICS_FWD_HPP
