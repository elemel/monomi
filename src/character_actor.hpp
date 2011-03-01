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
        CharacterActor(CharacterType const *type,
                       CategoryFlag category = NEUTRAL_CATEGORY, int id = 0);

        CharacterType const *type() const;

        b2Body *body() const;
        b2Fixture *fixture() const;

        StatePtr state() const;
        void state(StatePtr state);

        Vector2 position() const;

        Vector2 velocity() const;
        void velocity(Vector2 const &velocity);

        CharacterControlFlagSet const &controlFlags() const;
        void controlFlags(CharacterControlFlagSet const &flags);

        bool upControlFlag() const;
        bool leftControlFlag() const;
        bool downControlFlag() const;
        bool rightControlFlag() const;

        bool runControlFlag() const;
        bool jumpControlFlag() const;
        bool actionControlFlag() const;

        CharacterSensorFlagSet const &sensorFlags() const;

        bool ceilingSensorFlag() const;
        bool leftWallSensorFlag() const;
        bool floorSensorFlag() const;
        bool rightWallSensorFlag() const;

        float ceilingRunAcceleration() const;
        float ceilingRunVelocity() const;
        float fallAcceleration() const;
        float fallVelocity() const;
        float jumpVelocity() const;
        float walkAcceleration() const;
        float walkVelocity() const;
        float runAcceleration() const;
        float runVelocity() const;
        float wallSlideAcceleration() const;
        float wallSlideVelocity() const;
        float wallRunAcceleration() const;
        float wallRunVelocity() const;
        float wallJumpVelocity() const;
        float wallJumpAngle() const;
        float stompAcceleration() const;
        float stompVelocity() const;

        CharacterTechniqueFlagSet const &techniqueFlags() const;
        void techniqueFlags(CharacterTechniqueFlagSet const &flags);

        bool ceilingRunTechniqueFlag() const;
        bool doubleJumpTechniqueFlag() const;
        bool glideTechniqueFlag() const;
        bool slideTechniqueFlag() const;
        bool stompTechniqueFlag() const;
        bool teleportTechniqueFlag() const;
        bool tripleJumpTechniqueFlag() const;
        bool wallJumpTechniqueFlag() const;
        bool wallRunTechniqueFlag() const;
        bool wallSlideTechniqueFlag() const;

        CharacterToolFlagSet const &toolFlags() const;
        void toolFlags(CharacterToolFlagSet const &flags);

        bool bambooFluteToolFlag() const;
        bool grapplingHookToolFlag() const;
        bool ironFanToolFlag() const;
        bool smokeBombsToolFlag() const;
        bool strawBasketToolFlag() const;
        bool throwingStarsToolFlag() const;
        bool tigerClawsToolFlag() const;

        void create(GameLogic *logic, Vector2 const &position);
        void destroy();

        void update(float dt);
        void print(std::ostream &out) const;

    private:
        CharacterType const *type_;
        CategoryFlag categoryFlag_;
        int id_;

        GameLogic *logic_;
        b2Body *body_;
        b2Fixture *fixture_;
        b2Fixture *ceilingSensorFixture_, *leftWallSensorFixture_,
                  *floorSensorFixture_, *rightWallSensorFixture_;
        StatePtr state_;

        CharacterControlFlagSet controlFlags_;
        CharacterSensorFlagSet sensorFlags_;
        CharacterTechniqueFlagSet techniqueFlags_;
        CharacterToolFlagSet toolFlags_;

        b2Fixture *createSensorFixture(Vector2 const &center, float radius);

        void updateSensors(float dt);
        void updateState(float dt);
    };

    inline CharacterActor::CharacterActor(CharacterType const *type,
                                          CategoryFlag category, int id) :
        type_(type),
        categoryFlag_(category),
        id_(id),
        logic_(0),
        body_(0),
        fixture_(0),
        ceilingSensorFixture_(0),
        leftWallSensorFixture_(0),
        floorSensorFixture_(0),
        rightWallSensorFixture_(0),
        techniqueFlags_(type->techniqueFlags()),
        toolFlags_(type->toolFlags())
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

    inline CharacterControlFlagSet const &CharacterActor::controlFlags() const
    {
        return controlFlags_;
    }

    inline void CharacterActor::controlFlags(CharacterControlFlagSet const &flags)
    {
        controlFlags_ = flags;
    }

    inline bool CharacterActor::upControlFlag() const
    {
        return controlFlags_.test(CHARACTER_UP_CONTROL);
    }

    inline bool CharacterActor::leftControlFlag() const
    {
        return controlFlags_.test(CHARACTER_LEFT_CONTROL);
    }

    inline bool CharacterActor::downControlFlag() const
    {
        return controlFlags_.test(CHARACTER_DOWN_CONTROL);
    }

    inline bool CharacterActor::rightControlFlag() const
    {
        return controlFlags_.test(CHARACTER_RIGHT_CONTROL);
    }

    inline bool CharacterActor::runControlFlag() const
    {
        return controlFlags_.test(CHARACTER_RUN_CONTROL);
    }

    inline bool CharacterActor::jumpControlFlag() const
    {
        return controlFlags_.test(CHARACTER_JUMP_CONTROL);
    }

    inline bool CharacterActor::actionControlFlag() const
    {
        return controlFlags_.test(CHARACTER_ACTION_CONTROL);
    }

    inline CharacterSensorFlagSet const &CharacterActor::sensorFlags() const
    {
        return sensorFlags_;
    }

    inline bool CharacterActor::ceilingSensorFlag() const
    {
        return sensorFlags_.test(CHARACTER_CEILING_SENSOR);
    }

    inline bool CharacterActor::leftWallSensorFlag() const
    {
        return sensorFlags_.test(CHARACTER_LEFT_WALL_SENSOR);
    }

    inline bool CharacterActor::floorSensorFlag() const
    {
        return sensorFlags_.test(CHARACTER_FLOOR_SENSOR);
    }

    inline bool CharacterActor::rightWallSensorFlag() const
    {
        return sensorFlags_.test(CHARACTER_RIGHT_WALL_SENSOR);
    }

    inline float CharacterActor::ceilingRunAcceleration() const
    {
        return type_->ceilingRunAcceleration();
    }

    inline float CharacterActor::ceilingRunVelocity() const
    {
        return type_->ceilingRunVelocity();
    }

    inline float CharacterActor::fallAcceleration() const
    {
        return type_->fallAcceleration();
    }

    inline float CharacterActor::fallVelocity() const
    {
        return type_->fallVelocity();
    }

    inline float CharacterActor::jumpVelocity() const
    {
        return type_->jumpVelocity();
    }

    inline float CharacterActor::walkAcceleration() const
    {
        return type_->walkAcceleration();
    }

    inline float CharacterActor::walkVelocity() const
    {
        return type_->walkVelocity();
    }

    inline float CharacterActor::runAcceleration() const
    {
        return type_->runAcceleration();
    }

    inline float CharacterActor::runVelocity() const
    {
        return type_->runVelocity();
    }

    inline float CharacterActor::wallSlideAcceleration() const
    {
        return type_->wallSlideAcceleration();
    }

    inline float CharacterActor::wallSlideVelocity() const
    {
        return type_->wallSlideVelocity();
    }

    inline float CharacterActor::wallRunAcceleration() const
    {
        return type_->wallRunAcceleration();
    }

    inline float CharacterActor::wallRunVelocity() const
    {
        return type_->wallRunVelocity();
    }

    inline float CharacterActor::wallJumpVelocity() const
    {
        return type_->wallJumpVelocity();
    }

    inline float CharacterActor::wallJumpAngle() const
    {
        return type_->wallJumpAngle();
    }

    inline float CharacterActor::stompAcceleration() const
    {
        return type_->stompAcceleration();
    }

    inline float CharacterActor::stompVelocity() const
    {
        return type_->stompVelocity();
    }

    inline CharacterTechniqueFlagSet const &CharacterActor::techniqueFlags() const
    {
        return techniqueFlags_;
    }

    inline void CharacterActor::techniqueFlags(CharacterTechniqueFlagSet const &flags)
    {
        techniqueFlags_ = flags;
    }

    inline bool CharacterActor::ceilingRunTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_CEILING_RUN_TECHNIQUE);
    }

    inline bool CharacterActor::doubleJumpTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_DOUBLE_JUMP_TECHNIQUE);
    }

    inline bool CharacterActor::glideTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_GLIDE_TECHNIQUE);
    }

    inline bool CharacterActor::slideTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_SLIDE_TECHNIQUE);
    }

    inline bool CharacterActor::stompTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_STOMP_TECHNIQUE);
    }

    inline bool CharacterActor::teleportTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_TELEPORT_TECHNIQUE);
    }

    inline bool CharacterActor::tripleJumpTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_TRIPLE_JUMP_TECHNIQUE);
    }

    inline bool CharacterActor::wallJumpTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_WALL_JUMP_TECHNIQUE);
    }

    inline bool CharacterActor::wallRunTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_WALL_RUN_TECHNIQUE);
    }

    inline bool CharacterActor::wallSlideTechniqueFlag() const
    {
        return techniqueFlags_.test(CHARACTER_WALL_SLIDE_TECHNIQUE);
    }

    inline CharacterToolFlagSet const &CharacterActor::toolFlags() const
    {
        return toolFlags_;
    }

    inline void CharacterActor::toolFlags(CharacterToolFlagSet const &flags)
    {
        toolFlags_ = flags;
    }

    inline bool CharacterActor::bambooFluteToolFlag() const
    {
        return toolFlags_.test(CHARACTER_BAMBOO_FLUTE_TOOL);
    }

    inline bool CharacterActor::grapplingHookToolFlag() const
    {
        return toolFlags_.test(CHARACTER_GRAPPLING_HOOK_TOOL);
    }

    inline bool CharacterActor::ironFanToolFlag() const
    {
        return toolFlags_.test(CHARACTER_IRON_FAN_TOOL);
    }

    inline bool CharacterActor::smokeBombsToolFlag() const
    {
        return toolFlags_.test(CHARACTER_SMOKE_BOMBS_TOOL);
    }

    inline bool CharacterActor::strawBasketToolFlag() const
    {
        return toolFlags_.test(CHARACTER_STRAW_BASKET_TOOL);
    }

    inline bool CharacterActor::throwingStarsToolFlag() const
    {
        return toolFlags_.test(CHARACTER_THROWING_STARS_TOOL);
    }

    inline bool CharacterActor::tigerClawsToolFlag() const
    {
        return toolFlags_.test(CHARACTER_TIGER_CLAWS_TOOL);
    }
}

#endif // MONOMI_CHARACTER_ACTOR_HPP
