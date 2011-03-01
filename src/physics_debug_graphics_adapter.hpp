#ifndef MONOMI_PHYSICS_DEBUG_GRAPHICS_ADAPTER_HPP
#define MONOMI_PHYSICS_DEBUG_GRAPHICS_ADAPTER_HPP

#include <vector>
#include <Box2D/Common/b2Draw.h>
#include <Box2D/Common/b2Math.h>

namespace monomi {
    class DebugGraphics;

    class PhysicsDebugGraphicsAdapter : public b2Draw {
    public:
        explicit PhysicsDebugGraphicsAdapter(DebugGraphics *graphics);

        void DrawPolygon(b2Vec2 const *vertices, int32 vertexCount, b2Color const &color);
        void DrawSolidPolygon(b2Vec2 const *vertices, int32 vertexCount, b2Color const &color);
        void DrawCircle(b2Vec2 const &center, float32 radius, b2Color const &color);
        void DrawSolidCircle(b2Vec2 const &center, float32 radius, b2Vec2 const &axis, b2Color const &color);
        void DrawSegment(b2Vec2 const &p1, b2Vec2 const &p2, b2Color const &color);
        void DrawTransform(b2Transform const &transform);

    private:
        DebugGraphics *graphics_;
        b2Transform transform_;
        std::vector<float> vertices_;
    };
}

#endif // MONOMI_PHYSICS_DEBUG_GRAPHICS_ADAPTER_HPP
