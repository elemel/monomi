#include "character_actor.hpp"

#include "capitalize.hpp"
#include "character_states.hpp"
#include "game_logic.hpp"
#include "print_flags.hpp"
#include "state.hpp"
#include "type.hpp"

#include <iostream>
#include <sstream>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

namespace monomi {
    void CharacterActor::create(GameLogic *logic, Vector2 const &position)
    {
        logic_ = logic;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);
        bodyDef.userData = this;
        bodyDef.fixedRotation = true;
        body_ = logic_->world()->CreateBody(&bodyDef);

        b2CircleShape circleShape;
        circleShape.m_radius = 0.5f;

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.0f;
        fixtureDef.friction = 0.0f;
        fixtureDef.shape = &circleShape;
        fixtureDef.filter.categoryBits = 1 << categoryFlag_;
        switch (categoryFlag_) {
        case FRIEND_CATEGORY:
            fixtureDef.filter.maskBits = ~(1 << FRIEND_CATEGORY | 1 << NEUTRAL_CATEGORY);
            break;

        case NEUTRAL_CATEGORY:
            fixtureDef.filter.maskBits = ~(1 << FRIEND_CATEGORY | 1 << NEUTRAL_CATEGORY | 1 << ENEMY_CATEGORY);
            break;

        case ENEMY_CATEGORY:
            fixtureDef.filter.maskBits = ~(1 << NEUTRAL_CATEGORY | 1 << ENEMY_CATEGORY);
            break;

        default:
            break;
        }
        fixture_ = body_->CreateFixture(&fixtureDef);

        ceilingSensorFixture_ = createSensorFixture(Vector2(0.0f, 0.3f), 0.3f);
        leftWallSensorFixture_ = createSensorFixture(Vector2(-0.3f, 0.0f), 0.3f);
        floorSensorFixture_ = createSensorFixture(Vector2(0.0f, -0.3f), 0.3f);
        rightWallSensorFixture_ = createSensorFixture(Vector2(0.3f, 0.0f), 0.3f);

        state_.reset(new CharacterFallState(this));
        state_->enter();

        controlFlags_.set(CHARACTER_RUN_CONTROL, true);
    }

    void CharacterActor::destroy()
    {
        logic_->world()->DestroyBody(body_);
        body_ = 0;

        state_->leave();
        state_.reset();

        logic_ = 0;
    }

    void CharacterActor::update(float dt)
    {
        updateSensors(dt);
        updateState(dt);
    }

    void CharacterActor::print(std::ostream &out) const
    {
        out << type_->name() << "-" << id_;
    }

    b2Fixture *CharacterActor::createSensorFixture(Vector2 const &center,
                                                   float radius)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(center.x, center.y);
        circleShape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.filter.categoryBits = (1 << DEFAULT_CATEGORY);
        fixtureDef.filter.maskBits = (1 << PLATFORM_CATEGORY);
        fixtureDef.isSensor = true;

        return body_->CreateFixture(&fixtureDef);
    }

    void CharacterActor::updateSensors(float dt)
    {
        (void) dt;

        CharacterSensorFlagSet newSensorFlags;
        for (b2ContactEdge *edge = body_->GetContactList(); edge != 0;
             edge = edge->next)
        {
            if (edge->contact->IsTouching()) {
                b2Fixture *f1 = edge->contact->GetFixtureA();
                b2Fixture *f2 = edge->contact->GetFixtureB();
                if (f1 == ceilingSensorFixture_ || f2 == ceilingSensorFixture_) {
                    newSensorFlags.set(CHARACTER_CEILING_SENSOR);
                }
                if (f1 == leftWallSensorFixture_ || f2 == leftWallSensorFixture_) {
                    newSensorFlags.set(CHARACTER_LEFT_WALL_SENSOR);
                }
                if (f1 == floorSensorFixture_ || f2 == floorSensorFixture_) {
                    newSensorFlags.set(CHARACTER_FLOOR_SENSOR);
                }
                if (f1 == rightWallSensorFixture_ || f2 == rightWallSensorFixture_) {
                    newSensorFlags.set(CHARACTER_RIGHT_WALL_SENSOR);
                }
            }
        }

        if (newSensorFlags != sensorFlags_) {
            sensorFlags_ = newSensorFlags;
            std::ostringstream out;
            out << "DEBUG: " << capitalize(*this) << " changed sensors to ";
            printFlags<CharacterSensorFlag>(out, sensorFlags_);
            out << ".";
            std::cerr << out.str() << std::endl;
        }
    }

    void CharacterActor::updateState(float dt)
    {
        if (StatePtr state = state_->transition()) {
            state_->leave();
            state_ = state;
            std::cerr << "DEBUG: " << capitalize(*this) << " changed state to "
                      << *state_ << "." << std::endl;
            state_->enter();
        }
        state_->update(dt);
    }
}
