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
    {
        b2BodyDef bodyDef;
        worldBody_ = world_->CreateBody(&bodyDef);
    }

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

    void GameLogic::createPlatform(Polygon2 const &polygon)
    {
        int vertexCount = std::min(int(b2_maxPolygonVertices),
                                   int(polygon.vertices.size()));
        b2Vec2 vertices[b2_maxPolygonVertices];
        for (int i = 0; i < vertexCount; ++i) {
            vertices[i].Set(polygon.vertices[i].x, polygon.vertices[i].y);
        }

        b2PolygonShape polygonShape;
        polygonShape.Set(vertices, vertexCount);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createShadow(Polygon2 const &polygon)
    {
        int vertexCount = std::min(int(b2_maxPolygonVertices),
                                   int(polygon.vertices.size()));
        b2Vec2 vertices[b2_maxPolygonVertices];
        for (int i = 0; i < vertexCount; ++i) {
            vertices[i].Set(polygon.vertices[i].x, polygon.vertices[i].y);
        }

        b2PolygonShape polygonShape;
        polygonShape.Set(vertices, vertexCount);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createWater(Polygon2 const &polygon)
    {
        int vertexCount = std::min(int(b2_maxPolygonVertices),
                                   int(polygon.vertices.size()));
        b2Vec2 vertices[b2_maxPolygonVertices];
        for (int i = 0; i < vertexCount; ++i) {
            vertices[i].Set(polygon.vertices[i].x, polygon.vertices[i].y);
        }

        b2PolygonShape polygonShape;
        polygonShape.Set(vertices, vertexCount);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createStart(Circle2 const &circle)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(circle.center.x, circle.center.y);
        circleShape.m_radius = circle.radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createGoal(Circle2 const &circle)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(circle.center.x, circle.center.y);
        circleShape.m_radius = circle.radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        worldBody_->CreateFixture(&fixtureDef);
    }
}
