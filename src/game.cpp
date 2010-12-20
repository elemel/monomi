#include "game.hpp"

#include "block_actor.hpp"
#include "character_actor.hpp"
#include "character_factory.hpp"
#include "character_tag.hpp"
#include "character_type.hpp"
#include "component.hpp"
#include "random.hpp"

namespace monomi {
    namespace {
        boost::shared_ptr<BlockActor> createBlock(int x, int y)
        {
            boost::shared_ptr<BlockActor> block(new BlockActor);
            block->box.p1 = Point2(float(x), float(y));
            block->box.p2 = Point2(float(x + 1), float(y + 1));
            return block;
        }
    }

    Game::Game() :
        time_(0.0f),
        random_(new Random(std::time(0)))
    {
        characterFactory_.reset(new CharacterFactory(this));

        // Create characters.
        boost::shared_ptr<CharacterActor> character;
        character = characterFactory_->create(earthMasterTag);
        character->position = Point2(2.0f, 2.0f);
        addActor(character);
        character = characterFactory_->create(samuraiTag);
        character->position = Point2(7.0f, 5.0f);
        addActor(character);
        character = characterFactory_->create(samuraiTag);
        character->position = Point2(9.0f, 5.0f);
        addActor(character);
        character = characterFactory_->create(samuraiTag);
        character->position = Point2(11.0f, 5.0f);
        addActor(character);

        // Create blocks.
        addActor(createBlock(0, 0));
        addActor(createBlock(0, 3));
        addActor(createBlock(1, 0));
        addActor(createBlock(2, 0));
        addActor(createBlock(3, 0));
        addActor(createBlock(3, 1));
        addActor(createBlock(3, 2));
        addActor(createBlock(3, 3));
        addActor(createBlock(3, 4));
        addActor(createBlock(3, 5));
        addActor(createBlock(3, 6));
        addActor(createBlock(4, 0));
        addActor(createBlock(5, 0));
        addActor(createBlock(6, 0));
        addActor(createBlock(7, 0));
        addActor(createBlock(7, 3));
        addActor(createBlock(7, 4));
        addActor(createBlock(7, 5));
        addActor(createBlock(7, 6));
        addActor(createBlock(7, 7));
        addActor(createBlock(7, 8));
        addActor(createBlock(8, 0));
        addActor(createBlock(9, 0));
        addActor(createBlock(10, 0));
        addActor(createBlock(11, 0));
        addActor(createBlock(12, 0));
        addActor(createBlock(13, 0));
        addActor(createBlock(14, 0));
        addActor(createBlock(15, 0));
        addActor(createBlock(16, 0));
        addActor(createBlock(17, 0));
        addActor(createBlock(18, 0));
    }

    void Game::addActor(boost::shared_ptr<Actor> const &actor)
    {
        deferredActors_.push_back(actor);
    }

    void Game::update(float dt)
    {
        addDeferredActors();
        physicsComponents_.update(dt);
        collisionComponents_.update(dt);
    }

    void Game::addDeferredActors()
    {
        std::reverse(deferredActors_.begin(), deferredActors_.end());
        while (!deferredActors_.empty()) {
            boost::shared_ptr<Actor> actor = deferredActors_.back();
            deferredActors_.pop_back();
            actors_.push_back(actor);
            physicsComponents_.add(actor->physicsComponent());
            collisionComponents_.add(actor->collisionComponent());
        }
    }
}
