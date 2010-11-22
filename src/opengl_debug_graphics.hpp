#ifndef MONOMI_OPENGL_DEBUG_GRAPHICS_HPP
#define MONOMI_OPENGL_DEBUG_GRAPHICS_HPP

#include "debug_graphics.hpp"
#include "geometry.hpp"

#include <vector>
#include <boost/noncopyable.hpp>

namespace monomi {
    class OpenGLDebugGraphics :
        public DebugGraphics,
        private boost::noncopyable
    {
    public:
        explicit OpenGLDebugGraphics(int circleVertexCount = 16);

        virtual void drawLineSegment(const LineSegment2 &lineSegment);
        virtual void drawBox(const Box2 &box);
        virtual void drawCircle(const Circle &circle);

    protected:
        std::vector<Vector2> circleVertices_;
    };
}

#endif // MONOMI_OPENGL_DEBUG_GRAPHICS_HPP
