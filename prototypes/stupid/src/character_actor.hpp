#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"
#include "collision_category.hpp"
#include "geometry.hpp"
#include "support.hpp"

#include <bitset>
#include <Box2D/Dynamics/b2Body.h>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class State;

    enum Control {
        UP_CONTROL,
        LEFT_CONTROL,
        DOWN_CONTROL,
        RIGHT_CONTROL,

        JUMP_CONTROL,
        ACTION_CONTROL,

        CONTROL_COUNT
    };

    class CharacterActor : public Actor {
    public:
        typedef boost::shared_ptr<State> StatePtr;

        CharacterActor(Vector2 const &position, CollisionCategory category);

        StatePtr state() const;
        void state(StatePtr state);

        b2Body *body() const;
        void body(b2Body *body);

        bool testControl(Control control) const;
        void setControl(Control control, bool value);

        bool testSupport(Support support) const;

        void create(GameLogic *logic);
        void destroy();

        void update(float dt);

    private:
        typedef std::bitset<CONTROL_COUNT> ControlBits;
        typedef std::bitset<SUPPORT_COUNT> SupportBits;

        Vector2 position_;
        CollisionCategory category_;
        GameLogic *logic_;
        StatePtr state_;
        b2Body *body_;
        b2Fixture *leftSensor_, *rightSensor_, *downSensor_, *upSensor_;
        ControlBits controls_;
        SupportBits supports_;

        b2Fixture *createSensor(Vector2 const &center, float radius);

        void updateSupports(float dt);
        void updateState(float dt);
    };

    inline CharacterActor::CharacterActor(Vector2 const &position, CollisionCategory category) :
        position_(position),
        category_(category),
        logic_(0),
        body_(0),
        leftSensor_(0), rightSensor_(0), downSensor_(0), upSensor_(0)
    { }

    inline CharacterActor::StatePtr CharacterActor::state() const
    {
        return state_;
    }

    inline void CharacterActor::state(StatePtr state)
    {
        state_ = state;
    }

    inline b2Body *CharacterActor::body() const
    {
        return body_;
    }

    inline void CharacterActor::body(b2Body *body)
    {
        body_ = body;
    }

    inline bool CharacterActor::testControl(Control control) const
    {
        return controls_.test(control);
    }

    inline void CharacterActor::setControl(Control control, bool value)
    {
        controls_.set(control, value);
    }

    inline bool CharacterActor::testSupport(Support support) const
    {
        return supports_.test(support);
    }
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
