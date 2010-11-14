#ifndef MONOMI_GL_DEBUG_GRAPHICS_HPP
#define MONOMI_GL_DEBUG_GRAPHICS_HPP

#include "debug_graphics.hpp"
#include "geometry.hpp"

#include <vector>

namespace monomi {
    class GLDebugGraphics : public DebugGraphics {
    public:
        explicit GLDebugGraphics(int circleVertexCount = 16);

        virtual void drawLineSegment(const LineSegment2 &lineSegment);
        virtual void drawBox(const Box2 &box);
        virtual void drawCircle(const Circle &circle);

    protected:
        std::vector<Vector2> circleVertices_;
    };
}

#endif // MONOMI_GL_DEBUG_GRAPHICS_HPP
