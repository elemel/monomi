#include "opengl_debug_graphics.hpp"

#include <cmath>
#include <GL/gl.h>

namespace monomi {
    OpenGLDebugGraphics::OpenGLDebugGraphics(int circleVertexCount)
    {
        for (int i = 0; i < circleVertexCount; ++i) {
            float angle = 2.0f * pi * float(i) / float(circleVertexCount);
            Vector2 vertex(std::cos(angle), std::sin(angle));
            circleVertices_.push_back(vertex);
        }
    }

    void OpenGLDebugGraphics::drawLineSegment(const LineSegment2 &lineSegment)
    {
        glBegin(GL_LINES);
        glVertex2f(lineSegment.p1.x, lineSegment.p1.y);
        glVertex2f(lineSegment.p2.x, lineSegment.p2.y);
        glEnd();
    }

    void OpenGLDebugGraphics::drawBox(const Box2 &box)
    {
        glBegin(GL_LINES);
        glVertex2f(box.p1.x, box.p1.y);
        glVertex2f(box.p2.x, box.p1.y);
        glVertex2f(box.p2.x, box.p1.y);
        glVertex2f(box.p2.x, box.p2.y);
        glVertex2f(box.p2.x, box.p2.y);
        glVertex2f(box.p1.x, box.p2.y);
        glVertex2f(box.p1.x, box.p2.y);
        glVertex2f(box.p1.x, box.p1.y);
        glEnd();
    }

    void OpenGLDebugGraphics::drawCircle(const Circle &circle)
    {
        glBegin(GL_LINES);
        for (std::size_t i = 0; i < circleVertices_.size(); ++i) {
            std::size_t j = (i + 1) % circleVertices_.size();
            Point2 p1 = circle.center + circle.radius * circleVertices_[i];
            Point2 p2 = circle.center + circle.radius * circleVertices_[j];
            glVertex2f(p1.x, p1.y);
            glVertex2f(p2.x, p2.y);
        }
        glEnd();
    }
}