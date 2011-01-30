#ifndef MONOMI_DEBUG_GRAPHICS_HPP
#define MONOMI_DEBUG_GRAPHICS_HPP

#include <vector>

namespace monomi {
    class DebugGraphics {
    public:
        explicit DebugGraphics(int circleVertexCount = 16);

        void drawCircle(float center[2], float radius);
        void drawPolygon(float *vertices, int vertexCount);

    private:
        std::vector<float> circleVertices_;
    };
}

#endif // MONOMI_DEBUG_GRAPHICS_HPP
