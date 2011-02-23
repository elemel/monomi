#include "physics_debug_graphics_adapter.hpp"

#include "debug_graphics.hpp"

#include <iostream>

namespace monomi {
    PhysicsDebugGraphicsAdapter::PhysicsDebugGraphicsAdapter(DebugGraphics *graphics) :
        graphics_(graphics)
    {
        transform_.SetIdentity();
    }

    void PhysicsDebugGraphicsAdapter::DrawPolygon(b2Vec2 const *vertices,
        int32 vertexCount, b2Color const &color)
    {
        (void) color;
        vertices_.resize(2 * vertexCount);
        for (int32 i = 0; i < vertexCount; ++i) {
            b2Vec2 vertex = b2Mul(transform_, vertices[i]);
            vertices_[2 * i] = vertex.x;
            vertices_[2 * i + 1] = vertex.y;
        }
        graphics_->drawPolygon(&vertices_[0], int(vertexCount));
    }

    void PhysicsDebugGraphicsAdapter::DrawSolidPolygon(b2Vec2 const *vertices,
        int32 vertexCount, b2Color const &color)
    {
        DrawPolygon(vertices, vertexCount, color);
    }

    void PhysicsDebugGraphicsAdapter::DrawCircle(b2Vec2 const &center,
        float32 radius, b2Color const &color)
    {
        (void) color;
        b2Vec2 transformedCenter = b2Mul(transform_, center);
        float centerArray[] = { transformedCenter.x, transformedCenter.y };
        graphics_->drawCircle(centerArray, radius);
    }

    void PhysicsDebugGraphicsAdapter::DrawSolidCircle(b2Vec2 const &center,
        float32 radius, b2Vec2 const &axis, b2Color const &color)
    {
        (void) axis;
        DrawCircle(center, radius, color);
    }

    void PhysicsDebugGraphicsAdapter::DrawSegment(b2Vec2 const &p1,
        b2Vec2 const &p2, b2Color const &color)
    {
        (void) color;
        b2Vec2 transformedP1 = b2Mul(transform_, p1);
        b2Vec2 transformedP2 = b2Mul(transform_, p2);
        float p1Array[] = { transformedP1.x, transformedP1.y };
        float p2Array[] = { transformedP2.x, transformedP2.y };
        graphics_->drawLine(p1Array, p2Array);
    }

    void PhysicsDebugGraphicsAdapter::DrawTransform(b2Transform const &transform)
    {
        transform_ = transform;
    }
}
