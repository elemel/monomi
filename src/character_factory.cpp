#include "character_factory.hpp"

#include "character.hpp"
#include "character_type.hpp"

namespace monomi {
    namespace {
        boost::shared_ptr<CharacterType> createNinjaType()
        {
            return boost::shared_ptr<CharacterType>(new CharacterType);
        }

        boost::shared_ptr<CharacterType> createSamuraiType()
        {
            boost::shared_ptr<CharacterType> type = createNinjaType();
            return type;
        }

        boost::shared_ptr<CharacterType> createEarthMasterType()
        {
            boost::shared_ptr<CharacterType> type = createNinjaType();
            type->width = 1.4f;
            type->height = 1.9f;
            type->techniques.set(dropTechnique);
            type->techniques.set(ledgeGrabTechnique);
            type->techniques.set(ledgeJumpTechnique);
            type->techniques.set(stompTechnique);
            return type;
        }

        boost::shared_ptr<CharacterType> createFireMasterType()
        {
            boost::shared_ptr<CharacterType> type = createNinjaType();
            type->techniques.set(chargeTechnique);
            type->techniques.set(wallJumpTechnique);
            type->techniques.set(wallSlideTechnique);
            type->tools.set(smokeBombTool);
            type->tools.set(tigerClawTool);
            return type;
        }

        boost::shared_ptr<CharacterType> createAirMasterType()
        {
            boost::shared_ptr<CharacterType> type = createNinjaType();
            type->techniques.set(doubleJumpTechnique);
            type->techniques.set(slowFallTechnique);
            type->techniques.set(sprintTechnique);
            type->techniques.set(tripleJumpTechnique);
            type->tools.set(ironFanTool);
            type->tools.set(throwingStarTool);
            return type;
        }

        boost::shared_ptr<CharacterType> createWaterMasterType()
        {
            boost::shared_ptr<CharacterType> type = createNinjaType();
            type->techniques.set(diveTechnique);
            type->techniques.set(swimTechnique);
            type->tools.set(grapplingHookTool);
            return type;
        }

        boost::shared_ptr<CharacterType> createVoidMasterType()
        {
            boost::shared_ptr<CharacterType> type = createNinjaType();
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

    boost::shared_ptr<Character> CharacterFactory::createNinja()
    {
        return boost::shared_ptr<Character>(new Character(ninjaType_.get()));
    }

    boost::shared_ptr<Character> CharacterFactory::createSamurai()
    {
        return boost::shared_ptr<Character>(new Character(samuraiType_.get()));
    }

    boost::shared_ptr<Character> CharacterFactory::createEarthMaster()
    {
        return boost::shared_ptr<Character>(new Character(earthMasterType_.get()));
    }

    boost::shared_ptr<Character> CharacterFactory::createFireMaster()
    {
        return boost::shared_ptr<Character>(new Character(fireMasterType_.get()));
    }

    boost::shared_ptr<Character> CharacterFactory::createAirMaster()
    {
        return boost::shared_ptr<Character>(new Character(airMasterType_.get()));
    }

    boost::shared_ptr<Character> CharacterFactory::createWaterMaster()
    {
        return boost::shared_ptr<Character>(new Character(waterMasterType_.get()));
    }

    boost::shared_ptr<Character> CharacterFactory::createVoidMaster()
    {
        return boost::shared_ptr<Character>(new Character(voidMasterType_.get()));
    }
}
