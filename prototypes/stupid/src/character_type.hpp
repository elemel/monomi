#ifndef MONOMI_CHARACTER_TYPE_HPP
#define MONOMI_CHARACTER_TYPE_HPP

#include "category_flag.hpp"

#include <string>

namespace monomi {
    class CharacterType {
    public:
        CharacterType();

        std::string const &name() const;
        void name(std::string const &name);

        CategoryFlag category() const;
        void category(CategoryFlag category);

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

        float wallSlideVelocity() const;
        void wallSlideVelocity(float wallSlideVelocity);

        float wallRunVelocity() const;
        void wallRunVelocity(float wallRunVelocity);

    private:
        std::string name_;
        CategoryFlag category_;
        float jumpVelocity_;
        float walkAcceleration_;
        float walkVelocity_;
        float runAcceleration_;
        float runVelocity_;
        float wallSlideVelocity_;
        float wallRunVelocity_;
    };

    inline CharacterType::CharacterType() :
        category_(NEUTRAL_CATEGORY_FLAG),
        jumpVelocity_(10.0f),
        walkAcceleration_(10.0f),
        walkVelocity_(4.0f),
        runAcceleration_(10.0f),
        runVelocity_(7.0f),
        wallSlideVelocity_(5.0f),
        wallRunVelocity_(5.0f)
    { }

    inline std::string const &CharacterType::name() const
    {
        return name_;
    }

    inline void CharacterType::name(std::string const &name)
    {
        name_ = name;
    }

    inline CategoryFlag CharacterType::category() const
    {
        return category_;
    }

    inline void CharacterType::category(CategoryFlag category)
    {
        category_ = category;
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

    inline float CharacterType::wallSlideVelocity() const
    {
        return wallSlideVelocity_;
    }

    inline void CharacterType::wallSlideVelocity(float wallSlideVelocity)
    {
        wallSlideVelocity_ = wallSlideVelocity;
    }

    inline float CharacterType::wallRunVelocity() const
    {
        return wallRunVelocity_;
    }

    inline void CharacterType::wallRunVelocity(float wallRunVelocity)
    {
        wallRunVelocity_ = wallRunVelocity;
    }
}

#endif // MONOMI_CHARACTER_TYPE_HPP
