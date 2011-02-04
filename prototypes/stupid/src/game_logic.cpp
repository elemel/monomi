#include "game_logic.hpp"

#include "physics_debug_graphics_adapter.hpp"

#include <iostream>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace monomi {
    GameLogic::GameLogic() :
        time_(0.0f),
        world_(new b2World(b2Vec2(0.0f, -10.0f), true))
    { }

    void GameLogic::update(float dt)
    {
        time_ += dt;
        world_->Step(dt, 10, 10);
    }

    void GameLogic::debugDraw(DebugGraphics *graphics) {
        PhysicsDebugGraphicsAdapter adapter(graphics);
        adapter.SetFlags(b2DebugDraw::e_shapeBit);
        world_->SetDebugDraw(&adapter);
        world_->DrawDebugData();
        world_->SetDebugDraw(0);
    }

    void GameLogic::createCircleBody(Circle2 const &circle)
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(circle.center.x, circle.center.y);
        b2Body *body = world_->CreateBody(&bodyDef);

        b2CircleShape circleShape;
        circleShape.m_radius = circle.radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        b2Fixture *fixture = body->CreateFixture(&fixtureDef);
    }

    void GameLogic::createPolygonBody(Polygon2 const &polygon)
    {
        int vertexCount = std::min(int(b2_maxPolygonVertices),
                                   int(polygon.vertices.size()));
        b2Vec2 vertices[b2_maxPolygonVertices];
        for (int i = 0; i < vertexCount; ++i) {
            vertices[i].Set(polygon.vertices[i].x, polygon.vertices[i].y);
        }

        b2BodyDef bodyDef;
        b2Body *body = world_->CreateBody(&bodyDef);

        b2PolygonShape polygonShape;
        polygonShape.Set(vertices, vertexCount);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        b2Fixture *fixture = body->CreateFixture(&fixtureDef);
    }
}
