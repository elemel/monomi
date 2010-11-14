#ifndef MONOMI_DEBUG_GRAPHICS_HPP
#define MONOMI_DEBUG_GRAPHICS_HPP

#include <boost/noncopyable.hpp>

namespace monomi {
    class Box2;
    class Circle;
    class LineSegment2;

    class DebugGraphics :
        private boost::noncopyable
    {
    public:
        virtual ~DebugGraphics();

        virtual void drawLineSegment(const LineSegment2 &lineSegment) = 0;
        virtual void drawBox(const Box2 &box) = 0;
        virtual void drawCircle(const Circle &circle) = 0;
    };
}

#endif // MONOMI_DEBUG_GRAPHICS_HPP
