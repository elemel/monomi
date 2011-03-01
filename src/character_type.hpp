#ifndef MONOMI_CHARACTER_TYPE_HPP
#define MONOMI_CHARACTER_TYPE_HPP

#include "character_flags.hpp"

#include <bitset>
#include <cmath>
#include <string>

namespace monomi {
    class CharacterType {
    public:
        CharacterType();

        std::string const &name() const;
        void name(std::string const &name);

        float ceilingRunAcceleration() const;
        void ceilingRunAcceleration(float ceilingRunAcceleration);

        float ceilingRunVelocity() const;
        void ceilingRunVelocity(float ceilingRunVelocity);

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

        CharacterTechniqueSet const &techniques() const;
        void techniques(CharacterTechniqueSet const &techniques);

        CharacterToolSet const &tools() const;
        void tools(CharacterToolSet const &tools);

    private:
        std::string name_;

        float ceilingRunAcceleration_;
        float ceilingRunVelocity_;
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

        CharacterTechniqueSet techniques_;
        CharacterToolSet tools_;
    };

    inline CharacterType::CharacterType() :
        ceilingRunAcceleration_(0.0f),
        ceilingRunVelocity_(0.0f),
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

    inline float CharacterType::ceilingRunAcceleration() const
    {
        return ceilingRunAcceleration_;
    }

    inline void CharacterType::ceilingRunAcceleration(float ceilingRunAcceleration)
    {
        ceilingRunAcceleration_ = ceilingRunAcceleration;
    }

    inline float CharacterType::ceilingRunVelocity() const
    {
        return ceilingRunVelocity_;
    }

    inline void CharacterType::ceilingRunVelocity(float ceilingRunVelocity)
    {
        ceilingRunVelocity_ = ceilingRunVelocity;
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

    inline CharacterTechniqueSet const &CharacterType::techniques() const
    {
        return techniques_;
    }

    inline void CharacterType::techniques(CharacterTechniqueSet const &techniques)
    {
        techniques_ = techniques;
    }

    inline CharacterToolSet const &CharacterType::tools() const
    {
        return tools_;
    }

    inline void CharacterType::tools(CharacterToolSet const &tools)
    {
        tools_ = tools;
    }
}

#endif // MONOMI_CHARACTER_TYPE_HPP
