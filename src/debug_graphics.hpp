#ifndef MONOMI_DEBUG_GRAPHICS_HPP
#define MONOMI_DEBUG_GRAPHICS_HPP

#include <vector>

namespace monomi {
    class DebugGraphics {
    public:
        explicit DebugGraphics(int circleVertexCount = 16);

        void drawCircle(float center[2], float radius);
        void drawPolygon(float *vertices, int vertexCount);
        void drawLine(float p1[2], float p2[2]);

    private:
        std::vector<float> circleVertices_;
    };
}

#endif // MONOMI_DEBUG_GRAPHICS_HPP
