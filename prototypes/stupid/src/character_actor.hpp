#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"

#include <bitset>
#include <Box2D/Dynamics/b2Body.h>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class State;

    class CharacterActor : public Actor {
    public:
        typedef boost::shared_ptr<State> StatePtr;

        enum Control {
            actionControl,
            downControl,
            jumpControl,
            leftControl,
            rightControl,
            upControl,

            controlCount
        };

        CharacterActor();

        StatePtr state() const;
        void state(StatePtr state);

        b2Body *body() const;
        void body(b2Body *body);

        bool testControl(Control control) const;
        void setControl(Control control, bool value);

        void update(float dt);

    private:
        typedef std::bitset<controlCount> ControlBits;

        StatePtr state_;
        b2Body *body_;
        ControlBits controls_;
    };

    inline CharacterActor::CharacterActor() :
        body_(0)
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
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
