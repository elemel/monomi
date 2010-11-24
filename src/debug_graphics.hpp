#ifndef MONOMI_DEBUG_GRAPHICS_HPP
#define MONOMI_DEBUG_GRAPHICS_HPP

#include "geometry.hpp"

#include <vector>
#include <boost/noncopyable.hpp>

namespace monomi {
    class DebugGraphics :
        private boost::noncopyable
    {
    public:
        explicit DebugGraphics(int circleVertexCount = 16);

        void drawLineSegment(const LineSegment2 &lineSegment);
        void drawBox(const Box2 &box);
        void drawCircle(const Circle &circle);

    protected:
        std::vector<Vector2> circleVertices_;
    };
}

#endif // MONOMI_OPENGL_DEBUG_GRAPHICS_HPP
