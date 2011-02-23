#ifndef MONOMI_CHARACTER_TYPE_HPP
#define MONOMI_CHARACTER_TYPE_HPP

#include "character_technique_flag.hpp"
#include "character_tool_flag.hpp"

#include <bitset>
#include <cmath>
#include <string>

namespace monomi {
    class CharacterType {
    public:
        CharacterType();

        std::string const &name() const;
        void name(std::string const &name);

        float fallAcceleration() const;
        void fallAcceleration(float fallAcceleration);

        float fallVelocity() const;
        void fallVelocity(float fallVelocity);

        float jumpVelocity() const;
        void jumpVelocity(float jumpVelocity);

        float walkAcceleration() const;
        void walkAcceleration(float walkAcceleration);

        float walkVelocity() const;
        void walkVelocity(float walkVelocity);

        float runAcceleration() const;
        void runAcceleration(float runAcceleration);

        float runVelocity() const;
        void runVelocity(float runVelocity);

        float wallSlideAcceleration() const;
        void wallSlideAcceleration(float wallSlideAcceleration);

        float wallSlideVelocity() const;
        void wallSlideVelocity(float wallSlideVelocity);

        float wallRunAcceleration() const;
        void wallRunAcceleration(float wallRunAcceleration);

        float wallRunVelocity() const;
        void wallRunVelocity(float wallRunVelocity);

        float wallJumpVelocity() const;
        void wallJumpVelocity(float wallJumpVelocity);

        float wallJumpAngle() const;
        void wallJumpAngle(float wallJumpAngle);

        float stompAcceleration() const;
        void stompAcceleration(float stompAcceleration);

        float stompVelocity() const;
        void stompVelocity(float stompVelocity);

        CharacterTechniqueFlagSet const &techniqueFlags() const;
        void techniqueFlags(CharacterTechniqueFlagSet const &flags);

        CharacterToolFlagSet const &toolFlags() const;
        void toolFlags(CharacterToolFlagSet const &flags);

    private:
        std::string name_;

        float fallAcceleration_;
        float fallVelocity_;
        float jumpVelocity_;
        float runAcceleration_;
        float runVelocity_;
        float stompAcceleration_;
        float stompVelocity_;
        float walkAcceleration_;
        float walkVelocity_;
        float wallJumpAngle_;
        float wallJumpVelocity_;
        float wallRunAcceleration_;
        float wallRunVelocity_;
        float wallSlideAcceleration_;
        float wallSlideVelocity_;

        CharacterTechniqueFlagSet techniqueFlags_;
        CharacterToolFlagSet toolFlags_;
    };

    inline CharacterType::CharacterType() :
        fallAcceleration_(0.0f),
        fallVelocity_(0.0f),
        jumpVelocity_(0.0f),
        runAcceleration_(0.0f),
        runVelocity_(0.0f),
        stompAcceleration_(0.0f),
        stompVelocity_(0.0f),
        walkAcceleration_(0.0f),
        walkVelocity_(0.0f),
        wallJumpAngle_(0.0f),
        wallJumpVelocity_(0.0f),
        wallRunAcceleration_(0.0f),
        wallRunVelocity_(0.0f),
        wallSlideAcceleration_(0.0f),
        wallSlideVelocity_(0.0f)
    { }

    inline std::string const &CharacterType::name() const
    {
        return name_;
    }

    inline void CharacterType::name(std::string const &name)
    {
        name_ = name;
    }

    inline float CharacterType::fallAcceleration() const
    {
        return fallAcceleration_;
    }

    inline void CharacterType::fallAcceleration(float fallAcceleration)
    {
        fallAcceleration_ = fallAcceleration;
    }

    inline float CharacterType::fallVelocity() const
    {
        return fallVelocity_;
    }

    inline void CharacterType::fallVelocity(float fallVelocity)
    {
        fallVelocity_ = fallVelocity;
    }

    inline float CharacterType::jumpVelocity() const
    {
        return jumpVelocity_;
    }

    inline void CharacterType::jumpVelocity(float jumpVelocity)
    {
        jumpVelocity_ = jumpVelocity;
    }

    inline float CharacterType::walkAcceleration() const
    {
        return walkAcceleration_;
    }

    inline void CharacterType::walkAcceleration(float walkAcceleration)
    {
        walkAcceleration_ = walkAcceleration;
    }

    inline float CharacterType::walkVelocity() const
    {
        return walkVelocity_;
    }

    inline void CharacterType::walkVelocity(float walkVelocity)
    {
        walkVelocity_ = walkVelocity;
    }

    inline float CharacterType::runAcceleration() const
    {
        return runAcceleration_;
    }

    inline void CharacterType::runAcceleration(float runAcceleration)
    {
        runAcceleration_ = runAcceleration;
    }

    inline float CharacterType::runVelocity() const
    {
        return runVelocity_;
    }

    inline void CharacterType::runVelocity(float runVelocity)
    {
        runVelocity_ = runVelocity;
    }

    inline float CharacterType::wallSlideAcceleration() const
    {
        return wallSlideAcceleration_;
    }

    inline void CharacterType::wallSlideAcceleration(float wallSlideAcceleration)
    {
        wallSlideAcceleration_ = wallSlideAcceleration;
    }

    inline float CharacterType::wallSlideVelocity() const
    {
        return wallSlideVelocity_;
    }

    inline void CharacterType::wallSlideVelocity(float wallSlideVelocity)
    {
        wallSlideVelocity_ = wallSlideVelocity;
    }

    inline float CharacterType::wallRunAcceleration() const
    {
        return wallRunAcceleration_;
    }

    inline void CharacterType::wallRunAcceleration(float wallRunAcceleration)
    {
        wallRunAcceleration_ = wallRunAcceleration;
    }

    inline float CharacterType::wallRunVelocity() const
    {
        return wallRunVelocity_;
    }

    inline void CharacterType::wallRunVelocity(float wallRunVelocity)
    {
        wallRunVelocity_ = wallRunVelocity;
    }

    inline float CharacterType::wallJumpVelocity() const
    {
        return wallJumpVelocity_;
    }

    inline void CharacterType::wallJumpVelocity(float wallJumpVelocity)
    {
        wallJumpVelocity_ = wallJumpVelocity;
    }

    inline float CharacterType::wallJumpAngle() const
    {
        return wallJumpAngle_;
    }

    inline void CharacterType::wallJumpAngle(float wallJumpAngle)
    {
        wallJumpAngle_ = wallJumpAngle;
    }

    inline float CharacterType::stompAcceleration() const
    {
        return stompAcceleration_;
    }

    inline void CharacterType::stompAcceleration(float stompAcceleration)
    {
        stompAcceleration_ = stompAcceleration;
    }

    inline float CharacterType::stompVelocity() const
    {
        return stompVelocity_;
    }

    inline void CharacterType::stompVelocity(float stompVelocity)
    {
        stompVelocity_ = stompVelocity;
    }

    inline CharacterTechniqueFlagSet const &CharacterType::techniqueFlags() const
    {
        return techniqueFlags_;
    }

    inline void CharacterType::techniqueFlags(CharacterTechniqueFlagSet const &flags)
    {
        techniqueFlags_ = flags;
    }

    inline CharacterToolFlagSet const &CharacterType::toolFlags() const
    {
        return toolFlags_;
    }

    inline void CharacterType::toolFlags(CharacterToolFlagSet const &flags)
    {
        toolFlags_ = flags;
    }
}

#endif // MONOMI_CHARACTER_TYPE_HPP
