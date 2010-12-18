#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include <vector>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class BlockActor;
    class CharacterActor;
    class CharacterFactory;
    class Random;

    class Game {
    public:
        float time_;
        boost::shared_ptr<Random> random_;
        boost::shared_ptr<CharacterFactory> characterFactory_;
        std::vector<boost::shared_ptr<CharacterActor> > characters_;
        std::vector<boost::shared_ptr<BlockActor> > blocks_;

        Game();

        void update(float dt);
        void performAI(float dt);
        void resolveCollisions();
        void resolveBlockCollisions();
        void updateTouchFlags(CharacterActor *character);
        void resolveCharacterCollisions();
    };
}

#endif // MONOMI_GAME_HPP
