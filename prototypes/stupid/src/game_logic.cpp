#include "game_logic.hpp"

#include "physics_debug_graphics_adapter.hpp"

#include <iostream>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace monomi {
    GameLogic::GameLogic() :
        time_(0.0f),
        world_(new b2World(b2Vec2(0.0f, -10.0f), true))
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        b2Body *body = world_->CreateBody(&bodyDef);
        b2CircleShape circleShape;
        circleShape.m_radius = 1.0f;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        b2Fixture *fixture = body->CreateFixture(&fixtureDef);
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
}
