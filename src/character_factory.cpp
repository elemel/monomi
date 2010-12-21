#include "character_factory.hpp"

#include "character_actor.hpp"
#include "character_collision_component.hpp"
#include "character_physics_component.hpp"
#include "character_state_component.hpp"
#include "character_type.hpp"
#include "character_walk_state.hpp"

#include <stdexcept>

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

    CharacterFactory::CharacterFactory(Game *game) :
        game_(game)
    {
        types_[ninjaTag] = createNinjaType();
        types_[samuraiTag] = createSamuraiType();
        types_[earthMasterTag] = createEarthMasterType();
        types_[fireMasterTag] = createFireMasterType();
        types_[airMasterTag] = createAirMasterType();
        types_[waterMasterTag] = createFireMasterType();
        types_[voidMasterTag] = createVoidMasterType();
    }

    boost::shared_ptr<CharacterActor> CharacterFactory::create(CharacterTag tag) const
    {
        boost::shared_ptr<CharacterActor> character(new CharacterActor(types_[tag]));
        boost::shared_ptr<State> state(new CharacterWalkState(character.get(), game_));
        character->stateComponent_.reset(new CharacterStateComponent(character.get(), game_, state));
        character->physicsComponent_.reset(new CharacterPhysicsComponent(character.get(), game_));
        character->collisionComponent_.reset(new CharacterCollisionComponent(character.get(), game_));
        return character;
    }
}
