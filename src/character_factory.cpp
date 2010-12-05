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
            type->techniques.set(dropTechnique);
            type->techniques.set(ledgeGrabTechnique);
            type->techniques.set(ledgeJumpTechnique);
            type->techniques.set(stompTechnique);
            return type;
        }

        std::auto_ptr<CharacterType> createFireMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.set(chargeTechnique);
            type->techniques.set(wallJumpTechnique);
            type->techniques.set(wallSlideTechnique);
            type->tools.set(smokeBombTool);
            type->tools.set(tigerClawTool);
            return type;
        }

        std::auto_ptr<CharacterType> createAirMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.set(doubleJumpTechnique);
            type->techniques.set(slowFallTechnique);
            type->techniques.set(sprintTechnique);
            type->techniques.set(tripleJumpTechnique);
            type->tools.set(ironFanTool);
            type->tools.set(throwingStarTool);
            return type;
        }

        std::auto_ptr<CharacterType> createWaterMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.set(diveTechnique);
            type->techniques.set(swimTechnique);
            type->tools.set(grapplingHookTool);
            return type;
        }

        std::auto_ptr<CharacterType> createVoidMasterType()
        {
            std::auto_ptr<CharacterType> type = createNinjaType();
            type->techniques.set(disguiseTechnique);
            type->techniques.set(splitTechnique);
            type->techniques.set(teleportTechnique);
            type->tools.set(bambooFluteTool);
            type->tools.set(strawBasketTool);
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
