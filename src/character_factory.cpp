#include "character_factory.hpp"

#include "character.hpp"

namespace monomi {
    namespace {
        std::auto_ptr<CharacterType> createNinjaType()
        {
            return std::auto_ptr<CharacterType>(new CharacterType);
        }

        std::auto_ptr<CharacterType> createSamuraiType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            return type;
        }

        std::auto_ptr<CharacterType> createEarthMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->radius = 0.95f;
            type->techniques.drop = true;
            type->techniques.ledgeGrab = true;
            type->techniques.ledgeJump = true;
            type->techniques.slam = true;
            return type;
        }

        std::auto_ptr<CharacterType> createFireMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.charge = true;
            type->techniques.wallJump = true;
            type->techniques.wallSlide = true;
            type->equipment.smokeBombs = true;
            type->equipment.tigerClaws = true;
            return type;
        }

        std::auto_ptr<CharacterType> createAirMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.doubleJump = true;
            type->techniques.slowFall = true;
            type->techniques.sprint = true;
            type->techniques.tripleJump = true;
            type->equipment.ironFan = true;
            type->equipment.throwingStars = true;
            return type;
        }

        std::auto_ptr<CharacterType> createWaterMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.dive = true;
            type->techniques.swim = true;
            type->equipment.grapplingHook = true;
            return type;
        }

        std::auto_ptr<CharacterType> createVoidMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.disguise = true;
            type->techniques.split = true;
            type->techniques.teleport = true;
            type->equipment.bambooFlute = true;
            type->equipment.strawBasket = true;
            return type;
        }
    }

    CharacterFactory::CharacterFactory() :
        ninjaType_(createNinjaType()),
        samuraiType_(createSamuraiType()),
        earthMasterType_(createEarthMasterType()),
        fireMasterType_(createFireMasterType()),
        airMasterType_(createAirMasterType()),
        waterMasterType_(createFireMasterType()),
        voidMasterType_(createVoidMasterType())
    { }

    std::auto_ptr<Character> CharacterFactory::createNinja()
    {
        return std::auto_ptr<Character>(new Character(ninjaType_.get()));
    }

    std::auto_ptr<Character> CharacterFactory::createSamurai()
    {
        return std::auto_ptr<Character>(new Character(samuraiType_.get()));
    }

    std::auto_ptr<Character> CharacterFactory::createEarthMaster()
    {
        return std::auto_ptr<Character>(new Character(earthMasterType_.get()));
    }

    std::auto_ptr<Character> CharacterFactory::createFireMaster()
    {
        return std::auto_ptr<Character>(new Character(fireMasterType_.get()));
    }

    std::auto_ptr<Character> CharacterFactory::createAirMaster()
    {
        return std::auto_ptr<Character>(new Character(airMasterType_.get()));
    }

    std::auto_ptr<Character> CharacterFactory::createWaterMaster()
    {
        return std::auto_ptr<Character>(new Character(waterMasterType_.get()));
    }

    std::auto_ptr<Character> CharacterFactory::createVoidMaster()
    {
        return std::auto_ptr<Character>(new Character(voidMasterType_.get()));
    }
}
