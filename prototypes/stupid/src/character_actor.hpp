#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"
#include "category_flag.hpp"
#include "character_type.hpp"
#include "geometry.hpp"
#include "state_fwd.hpp"

#include <bitset>
#include <string>
#include <Box2D/Dynamics/b2Body.h>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class CharacterActor : public Actor {
    public:
        enum SensorFlag {
            CEILING_SENSOR,
            LEFT_WALL_SENSOR,
            RIGHT_WALL_SENSOR,
            FLOOR_SENSOR,

            SENSOR_COUNT
        };

        typedef std::bitset<SENSOR_COUNT> SensorFlagSet;

        enum ControlFlag {
            UP_CONTROL,
            LEFT_CONTROL,
            DOWN_CONTROL,
            RIGHT_CONTROL,

            RUN_CONTROL,
            JUMP_CONTROL,
            ACTION_CONTROL,

            CONTROL_COUNT
        };

        typedef std::bitset<CONTROL_COUNT> ControlFlagSet;

        CharacterActor(CharacterType const *type, int id = 0);

        CharacterType const *type() const;

        b2Body *body() const;
        b2Fixture *fixture() const;

        StatePtr state() const;
        void state(StatePtr state);

        Vector2 position() const;

        Vector2 velocity() const;
        void velocity(Vector2 const &velocity);

        ControlFlagSet const &controlFlags() const;
        void controlFlags(ControlFlagSet const &flags);

        SensorFlagSet const &sensorFlags() const;

        void create(GameLogic *logic, Vector2 const &position);
        void destroy();

        void update(float dt);
        void print(std::ostream &out) const;

    private:
        CharacterType const *type_;
        int id_;

        GameLogic *logic_;
        b2Body *body_;
        b2Fixture *fixture_;
        b2Fixture *ceilingSensorFixture_, *leftWallSensorFixture_,
                  *floorSensorFixture_, *rightWallSensorFixture_;
        StatePtr state_;

        ControlFlagSet controlFlags_;
        SensorFlagSet sensorFlags_;

        b2Fixture *createSensorFixture(Vector2 const &center, float radius);

        void updateSensors(float dt);
        void updateState(float dt);
    };


    std::ostream &operator<<(std::ostream &out, CharacterActor::SensorFlag sensor);

    inline CharacterActor::CharacterActor(CharacterType const *type, int id) :
        type_(type),
        id_(id),
        logic_(0),
        body_(0),
        fixture_(0),
        ceilingSensorFixture_(0),
        leftWallSensorFixture_(0),
        floorSensorFixture_(0),
        rightWallSensorFixture_(0)
    { }

    inline CharacterType const *CharacterActor::type() const
    {
        return type_;
    }

    inline b2Body *CharacterActor::body() const
    {
        return body_;
    }

    inline b2Fixture *CharacterActor::fixture() const
    {
        return fixture_;
    }

    inline StatePtr CharacterActor::state() const
    {
        return state_;
    }

    inline void CharacterActor::state(StatePtr state)
    {
        state_ = state;
    }

    inline Vector2 CharacterActor::position() const
    {
        assert(body_);
        b2Vec2 const &position = body_->GetPosition();
        return Vector2(position.x, position.y);
    }

    inline Vector2 CharacterActor::velocity() const
    {
        assert(body_);
        b2Vec2 const &linearVelocity = body_->GetLinearVelocity();
        return Vector2(linearVelocity.x, linearVelocity.y);
    }

    inline void CharacterActor::velocity(Vector2 const &velocity)
    {
        assert(body_);
        body_->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }

    inline CharacterActor::ControlFlagSet const &CharacterActor::controlFlags() const
    {
        return controlFlags_;
    }

    inline void CharacterActor::controlFlags(ControlFlagSet const &flags)
    {
        controlFlags_ = flags;
    }

    inline CharacterActor::SensorFlagSet const &CharacterActor::sensorFlags() const
    {
        return sensorFlags_;
    }
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
