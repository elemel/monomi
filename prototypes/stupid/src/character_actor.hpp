#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"

#include <bitset>
#include <Box2D/Dynamics/b2Body.h>

namespace monomi {
    class CharacterActor : public Actor {
    public:
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

        b2Body *body() const;
        void body(b2Body *body);

        bool testControl(Control control) const;
        void setControl(Control control, bool value);

    private:
        typedef std::bitset<controlCount> ControlBits;

        b2Body *body_;
        ControlBits controls_;
    };

    inline CharacterActor::CharacterActor() :
        body_(0)
    { }

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
