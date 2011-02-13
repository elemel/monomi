#include "character_actor.hpp"

#include "character_states.hpp"
#include "format_enum_bits.hpp"
#include "game_logic.hpp"
#include "state.hpp"

#include <iostream>
#include <sstream>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

namespace monomi {
    void CharacterActor::create(GameLogic *logic)
    {
        logic_ = logic;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position_.x, position_.y);
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
        fixtureDef.filter.categoryBits = (1 << category_);
        body_->CreateFixture(&fixtureDef);

        leftSensor_ = createSensor(Vector2(-0.2f, 0.0f), 0.4f);
        rightSensor_ = createSensor(Vector2(0.2f, 0.0f), 0.4f);
        downSensor_ = createSensor(Vector2(0.0f, -0.2f), 0.4f);
        upSensor_ = createSensor(Vector2(0.0f, 0.2f), 0.4f);

        state_.reset(new CharacterFallState(this));
        state_->enter();
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
        updateSupports(dt);
        updateState(dt);
    }

    b2Fixture *CharacterActor::createSensor(Vector2 const &center, float radius)
    {
        b2CircleShape circleShape;
        circleShape.m_p.Set(center.x, center.y);
        circleShape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.filter.categoryBits = (1 << category_);
        fixtureDef.filter.maskBits = (1 << platformCollisionCategory);
        fixtureDef.isSensor = true;

        return body_->CreateFixture(&fixtureDef);
    }

    void CharacterActor::updateSupports(float dt)
    {
        (void) dt;

        SupportBits newSupports;
        for (b2ContactEdge *edge = body_->GetContactList(); edge != 0;
             edge = edge->next)
        {
            if (edge->contact->IsTouching()) {
                b2Fixture *f1 = edge->contact->GetFixtureA();
                b2Fixture *f2 = edge->contact->GetFixtureB();
                if (f1 == leftSensor_ || f2 == leftSensor_) {
                    newSupports.set(LEFT_SUPPORT);
                }
                if (f1 == rightSensor_ || f2 == rightSensor_) {
                    newSupports.set(RIGHT_SUPPORT);
                }
                if (f1 == downSensor_ || f2 == downSensor_) {
                    newSupports.set(DOWN_SUPPORT);
                }
                if (f1 == upSensor_ || f2 == upSensor_) {
                    newSupports.set(UP_SUPPORT);
                }
            }
        }

        if (newSupports != supports_) {
            supports_ = newSupports;
            std::ostringstream out;
            out << "DEBUG: Character changed supports to ";
            formatEnumBits<Support>(out, supports_);
            out << ".";
            std::cerr << out.str() << std::endl;
        }
    }

    void CharacterActor::updateState(float dt)
    {
        if (CharacterActor::StatePtr state = state_->transition()) {
            state_->leave();
            state_ = state;
            std::cerr << "DEBUG: Character changed state to " << typeid(*state_).name() << "." << std::endl;
            state_->enter();
        }
        state_->update(dt);
    }
}
