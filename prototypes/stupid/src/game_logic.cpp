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
        world_(new b2World(b2Vec2(0.0f, 0.0f), true))
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

    void GameLogic::addCharacterType(CharacterTypePtr type)
    {
        characterTypes_[type->name()] = type;
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
        fixtureDef.filter.categoryBits = (1 << PLATFORM_CATEGORY);
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createShadow(Polygon2 const &polygon)
    {
        b2PolygonShape polygonShape;
        copy(polygon, polygonShape);

        b2FixtureDef fixtureDef;
        fixtureDef.isSensor = true;
        fixtureDef.shape = &polygonShape;
        fixtureDef.filter.categoryBits = (1 << SHADOW_CATEGORY);
        worldBody_->CreateFixture(&fixtureDef);
    }

    void GameLogic::createWater(Polygon2 const &polygon)
    {
        b2PolygonShape polygonShape;
        copy(polygon, polygonShape);

        b2FixtureDef fixtureDef;
        fixtureDef.isSensor = true;
        fixtureDef.shape = &polygonShape;
        fixtureDef.filter.categoryBits = (1 << WATER_CATEGORY);
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

    GameLogic::CharacterPtr GameLogic::createCharacter(std::string const &name,
                                                       Vector2 const &position)
    {
        CharacterTypeMap::const_iterator i = characterTypes_.find(name);
        assert(i != characterTypes_.end());
        boost::shared_ptr<CharacterActor> character(new CharacterActor(i->second.get()));
        character->create(this, position);
        characters_.push_back(character);
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
            playerCharacter_ = createCharacter("earth-master", position);
            std::cerr << "DEBUG: Created player character." << std::endl;
        }
    }

    namespace {
        struct CharacterRayCastCallback : b2RayCastCallback {
            uint16 maskBits_;
            b2Fixture *fixture_;
            b2Vec2 point_;
            b2Vec2 normal_;
            float32 fraction_;

            explicit CharacterRayCastCallback(uint16 maskBits) :
                maskBits_(maskBits),
                fixture_(0),
                point_(0.0f, 0.0f),
                normal_(0.0f, 0.0f),
                fraction_(1.0f)
            { }

	        float32 ReportFixture(b2Fixture *fixture, b2Vec2 const &point,
	                              b2Vec2 const &normal, float32 fraction)
	        {
	            if ((fixture->GetFilterData().categoryBits & maskBits_) != 0 &&
	                fraction < fraction_)
	            {
	                fixture_ = fixture;
	                point_ = point;
	                normal_ = normal;
	                fraction_ = fraction;
	            }
	            return fraction;
	        }
        };
    }

    void GameLogic::updateCharacters(float dt)
    {
        for (CharacterVector::iterator i = characters_.begin();
             i != characters_.end(); ++i)
        {
            CharacterRayCastCallback callback(1 << PLATFORM_CATEGORY);
            b2Vec2 p1 = (*i)->body()->GetPosition();
            b2Vec2 p2 = p1 + b2Vec2(0.0f, -1.0f);
            // world_->RayCast(&callback, p1, p2);
            if (callback.fraction_ < 0.75f) {
                b2Vec2 p3 = p1 + (0.75f - callback.fraction_) * b2Vec2(0.0f, 1.0f);
                std::cout << callback.fraction_ << " " << p1.y << " " << p3.y << std::endl;
                (*i)->body()->SetTransform(p3, 0.0f);
                (*i)->body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
            }
            (*i)->update(dt);
        }
    }
}
