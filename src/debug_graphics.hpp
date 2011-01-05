#ifndef MONOMI_DEBUG_GRAPHICS_HPP
#define MONOMI_DEBUG_GRAPHICS_HPP

#include "debug_graphics_fwd.hpp"

#include "debug_color.hpp"
#include "geometry.hpp"

#include <vector>
#include <boost/noncopyable.hpp>

namespace monomi {
    class DebugGraphics :
        private boost::noncopyable
    {
    public:
        explicit DebugGraphics(int circleVertexCount = 16);

        void draw(const LineSegment2 &lineSegment,
                  const DebugColor &color = debugColors::gray());
        void draw(const Box2 &box,
                  const DebugColor &color = debugColors::gray());
        void draw(const Circle &circle,
                  const DebugColor &color = debugColors::gray());

    protected:
        std::vector<Vector2> circleVertices_;
    };
}

#endif // MONOMI_DEBUG_GRAPHICS_HPP
