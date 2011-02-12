#include "game_logic.hpp"

#include "character_actor.hpp"
#include "character_states.hpp"
#include "physics_debug_graphics_adapter.hpp"
#include "state.hpp"

#include <iostream>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace monomi {
    namespace {
        void copy(Polygon2 const &source, b2PolygonShape &target)
        {
            int vertexCount = std::min(int(b2_maxPolygonVertices),
                                       int(source.vertices.size()));
            b2Vec2 vertices[b2_maxPolygonVertices];
            for (int i = 0; i < vertexCount; ++i) {
                vertices[i].Set(source.vertices[i].x, source.vertices[i].y);
            }
            target.Set(vertices, vertexCount);
        }
    }

    GameLogic::GameLogic() :
        time_(0.0f),
        world_(new b2World(b2Vec2(0.0f, -10.0f), true))
    {
        b2BodyDef bodyDef;
        worldBody_ = world_->CreateBody(&bodyDef);
    }

    float GameLogic::time() const
    {
        return  time_;
    }

    GameLogic::CharacterPtr GameLogic::playerCharacter() const
    {
        return playerCharacter_;
    }

    GameLogic::CharacterVector const &GameLogic::characters() const
    {
        return characters_;
    }

    void GameLogic::update(float dt)
    {
        time_ += dt;
        createPlayerCharacter();
        updateCharacters(dt);
        world_->Step(dt, 10, 10);
    }

    void GameLogic::debugDraw(DebugGraphics *graphics)
    {
        PhysicsDebugGraphicsAdapter adapter(graphics);
        adapter.SetFlags(b2DebugDraw::e_shapeBit);
        world_->SetDebugDraw(&adapter);
        world_->DrawDebugData();
        world_->SetDebugDraw(0);
    }

    void GameLogic::createPlatform(Polygon2 const &polygon)
    {
        b2PolygonShape polygonShape;
        copy(polygon, polygonShape);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createShadow(Polygon2 const &polygon)
    {
        b2PolygonShape polygonShape;
        copy(polygon, polygonShape);

        b2FixtureDef fixtureDef;
        fixtureDef.isSensor = true;
        fixtureDef.shape = &polygonShape;
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createWater(Polygon2 const &polygon)
    {
        b2PolygonShape polygonShape;
        copy(polygon, polygonShape);

        b2FixtureDef fixtureDef;
        fixtureDef.isSensor = true;
        fixtureDef.shape = &polygonShape;
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createStart(Circle2 const &circle)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(circle.center.x, circle.center.y);
        circleShape.m_radius = circle.radius;

        b2FixtureDef fixtureDef;
        fixtureDef.isSensor = true;
        fixtureDef.shape = &circleShape;
        b2Fixture *fixture = worldBody_->CreateFixture(&fixtureDef);
        startFixtures_.push_back(fixture);

        startPositions_.push_back(circle.center);
    }

    void GameLogic::createGoal(Circle2 const &circle)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(circle.center.x, circle.center.y);
        circleShape.m_radius = circle.radius;

        b2FixtureDef fixtureDef;
        fixtureDef.isSensor = true;
        fixtureDef.shape = &circleShape;
        b2Fixture *fixture = worldBody_->CreateFixture(&fixtureDef);
        goalFixtures_.push_back(fixture);
    }

    GameLogic::CharacterPtr GameLogic::createCharacter(Vector2 const &position)
    {
        boost::shared_ptr<CharacterActor> character(new CharacterActor);

        boost::shared_ptr<State> state(new CharacterFallState(*character));
        character->state(state);

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);
        bodyDef.userData = character.get();
        b2Body *body = world_->CreateBody(&bodyDef);

        character->body(body);

        b2CircleShape circleShape;
        circleShape.m_radius = 0.5f;

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0f;
        fixtureDef.shape = &circleShape;
        body->CreateFixture(&fixtureDef);

        characters_.push_back(character);
        character->state()->enter();
        return character;
    }

    void GameLogic::destroyCharacter(CharacterPtr character)
    {
        CharacterVector::iterator i = std::find(characters_.begin(),
                                                characters_.end(), character);
        assert(i != characters_.end());
        character->state()->leave();
        characters_.erase(i);
    }

    void GameLogic::createPlayerCharacter()
    {
        if (!playerCharacter_&& !startPositions_.empty()) {
            Vector2 position = startPositions_.front();
            playerCharacter_ = createCharacter(position);
            std::cerr << "DEBUG: Created player character." << std::endl;
        }
    }

    void GameLogic::updateCharacters(float dt)
    {
        for (CharacterVector::iterator i = characters_.begin();
             i != characters_.end(); ++i)
        {
            (*i)->update(dt);
        }
    }
}
