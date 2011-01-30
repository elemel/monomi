#include "debug_graphics.hpp"

#include <cmath>
#include <SDL_opengl.h>

namespace monomi {
    DebugGraphics::DebugGraphics(int circleVertexCount) :
        circleVertices_(2 * circleVertexCount)
    {
        for (int i = 0; i < circleVertexCount; ++i) {
            float angle = 2.0f * M_PI * float(i) / float(circleVertexCount);
            circleVertices_[2 * i] = std::cos(angle);
            circleVertices_[2 * i + 1] = std::sin(angle);
        }
    }

    void DebugGraphics::drawCircle(float center[2], float radius)
    {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; 2 * i < circleVertices_.size(); ++i) {
            glVertex2f(center[0] + radius * circleVertices_[2 * i],
                       center[1] + radius * circleVertices_[2 * i + 1]);
        }
        glEnd();
    }

    void DebugGraphics::drawPolygon(float *vertices, int vertexCount)
    {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < vertexCount; ++i) {
            glVertex2f(vertices[2 * i], vertices[2 * i + 1]);
        }
        glEnd();
    }

    void DebugGraphics::drawLine(float p1[2], float p2[2])
    {
        glBegin(GL_LINES);
        glVertex2f(p1[0], p1[1]);
        glVertex2f(p2[0], p2[1]);
        glEnd();
    }
}
