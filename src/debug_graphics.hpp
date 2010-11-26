#ifndef MONOMI_DEBUG_GRAPHICS_HPP
#define MONOMI_DEBUG_GRAPHICS_HPP

#include "geometry.hpp"

#include <vector>
#include <boost/noncopyable.hpp>

namespace monomi {
    class DebugColor {
    public:
        float red, green, blue;

        DebugColor();
        DebugColor(float red, float green, float blue);
    };

    namespace debugColors {
        DebugColor black();
        DebugColor blue();
        DebugColor cyan();
        DebugColor gray();
        DebugColor green();
        DebugColor magenta();
        DebugColor red();
        DebugColor white();
        DebugColor yellow();
    }

    class DebugGraphics :
        private boost::noncopyable
    {
    public:
        explicit DebugGraphics(int circleVertexCount = 16);

        void drawLineSegment(const LineSegment2 &lineSegment,
                             const DebugColor &color = debugColors::gray());
        void drawBox(const Box2 &box,
                     const DebugColor &color = debugColors::gray());
        void drawCircle(const Circle &circle,
                        const DebugColor &color = debugColors::gray());

    protected:
        std::vector<Vector2> circleVertices_;
    };
}

#endif // MONOMI_OPENGL_DEBUG_GRAPHICS_HPP
