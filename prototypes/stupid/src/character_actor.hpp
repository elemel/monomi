#ifndef MONOMI_CHARACTER_ACTOR_HPP
#define MONOMI_CHARACTER_ACTOR_HPP

#include "actor.hpp"
#include "category_flag.hpp"
#include "contact_flag.hpp"
#include "geometry.hpp"
#include "input_flag.hpp"

#include <bitset>
#include <string>
#include <Box2D/Dynamics/b2Body.h>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class State;

    class CharacterActor : public Actor {
    public:
        typedef boost::shared_ptr<State> StatePtr;

        CharacterActor(CategoryFlag category, std::string const &name);

        Vector2 position() const;

        void horizontalVelocity(float horizontalVelocity);

        void verticalVelocity(float verticalVelocity);

        StatePtr state() const;
        void state(StatePtr state);

        b2Body *body() const;
        void body(b2Body *body);

        bool testInput(InputFlag input) const;
        void setInput(InputFlag input, bool value);

        bool testContact(ContactFlag contact) const;

        void create(GameLogic *logic, Vector2 const &position);
        void destroy();

        void update(float dt);
        void print(std::ostream &out) const;

    private:
        typedef std::bitset<INPUT_FLAG_COUNT> InputFlagSet;
        typedef std::bitset<CONTACT_FLAG_COUNT> ContactFlagSet;

        CategoryFlag category_;
        std::string name_;
        GameLogic *logic_;
        StatePtr state_;
        b2Body *body_;
        b2Fixture *leftSensor_, *rightSensor_, *downSensor_, *upSensor_;
        InputFlagSet inputs_;
        ContactFlagSet contacts_;

        b2Fixture *createSensor(Vector2 const &center, float radius);

        void updateContacts(float dt);
        void updateState(float dt);
    };

    inline CharacterActor::CharacterActor(CategoryFlag category,
                                          std::string const &name) :
        category_(category),
        name_(name),
        logic_(0),
        body_(0),
        leftSensor_(0), rightSensor_(0), downSensor_(0), upSensor_(0)
    { }

    inline Vector2 CharacterActor::position() const
    {
        assert(body_);
        b2Vec2 const &position = body_->GetPosition();
        return Vector2(position.x, position.y);
    }

    inline void CharacterActor::horizontalVelocity(float horizontalVelocity)
    {
        assert(body_);
        b2Vec2 linearVelocity = body_->GetLinearVelocity();
        linearVelocity.x = horizontalVelocity;
        body_->SetLinearVelocity(linearVelocity);
    }

    inline void CharacterActor::verticalVelocity(float verticalVelocity)
    {
        assert(body_);
        b2Vec2 linearVelocity = body_->GetLinearVelocity();
        linearVelocity.y = verticalVelocity;
        body_->SetLinearVelocity(linearVelocity);
    }

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

    inline bool CharacterActor::testInput(InputFlag input) const
    {
        return inputs_.test(input);
    }

    inline void CharacterActor::setInput(InputFlag input, bool value)
    {
        inputs_.set(input, value);
    }

    inline bool CharacterActor::testContact(ContactFlag contact) const
    {
        return contacts_.test(contact);
    }
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
