#include "game.hpp"

#include "block_actor.hpp"
#include "character_actor.hpp"
#include "character_factory.hpp"
#include "character_tag.hpp"
#include "character_type.hpp"
#include "physics.hpp"
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
        random_(new Random(std::time(0))),
        characterFactory_(new CharacterFactory)
    {
        physics_.reset(new Physics(this));

        // Create characters.
        characters_.push_back(characterFactory_->create(earthMasterTag));
        characters_.back()->position = Point2(2.0f, 2.0f);
        characters_.push_back(characterFactory_->create(samuraiTag));
        characters_.back()->position = Point2(7.0f, 5.0f);
        characters_.push_back(characterFactory_->create(samuraiTag));
        characters_.back()->position = Point2(9.0f, 5.0f);
        characters_.push_back(characterFactory_->create(samuraiTag));
        characters_.back()->position = Point2(11.0f, 5.0f);

        // Create blocks.
        blocks_.push_back(createBlock(0, 0));
        blocks_.push_back(createBlock(0, 3));
        blocks_.push_back(createBlock(1, 0));
        blocks_.push_back(createBlock(2, 0));
        blocks_.push_back(createBlock(3, 0));
        blocks_.push_back(createBlock(3, 1));
        blocks_.push_back(createBlock(3, 2));
        blocks_.push_back(createBlock(3, 3));
        blocks_.push_back(createBlock(3, 4));
        blocks_.push_back(createBlock(3, 5));
        blocks_.push_back(createBlock(3, 6));
        blocks_.push_back(createBlock(4, 0));
        blocks_.push_back(createBlock(5, 0));
        blocks_.push_back(createBlock(6, 0));
        blocks_.push_back(createBlock(7, 0));
        blocks_.push_back(createBlock(7, 3));
        blocks_.push_back(createBlock(7, 4));
        blocks_.push_back(createBlock(7, 5));
        blocks_.push_back(createBlock(7, 6));
        blocks_.push_back(createBlock(7, 7));
        blocks_.push_back(createBlock(7, 8));
        blocks_.push_back(createBlock(8, 0));
        blocks_.push_back(createBlock(9, 0));
        blocks_.push_back(createBlock(10, 0));
        blocks_.push_back(createBlock(11, 0));
        blocks_.push_back(createBlock(12, 0));
        blocks_.push_back(createBlock(13, 0));
        blocks_.push_back(createBlock(14, 0));
        blocks_.push_back(createBlock(15, 0));
        blocks_.push_back(createBlock(16, 0));
        blocks_.push_back(createBlock(17, 0));
        blocks_.push_back(createBlock(18, 0));
    }

    void Game::update(float dt)
    {
        physics_->update(dt);
    }
}
