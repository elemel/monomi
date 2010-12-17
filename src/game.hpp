#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include <vector>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class Block;
    class Character;
    class CharacterFactory;
    class Random;

    class Game {
    public:
        float time_;
        boost::shared_ptr<Random> random_;
        boost::shared_ptr<CharacterFactory> characterFactory_;
        std::vector<boost::shared_ptr<Character> > characters_;
        std::vector<boost::shared_ptr<Block> > blocks_;

        Game();

        void step(float dt);
        void performAI(float dt);
        void resolveCollisions();
        void resolveBlockCollisions();
        void updateTouchFlags(Character *character);
        void resolveCharacterCollisions();
    };
}

#endif // MONOMI_GAME_HPP
