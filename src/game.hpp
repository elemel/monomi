#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include <vector>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class BlockActor;
    class CharacterActor;
    class CharacterFactory;
    class Physics;
    class Random;

    class Game {
    public:
        float time_;
        boost::shared_ptr<Random> random_;
        boost::shared_ptr<CharacterFactory> characterFactory_;
        std::vector<boost::shared_ptr<CharacterActor> > characters_;
        std::vector<boost::shared_ptr<BlockActor> > blocks_;
        boost::shared_ptr<Physics> physics_;

        Game();

        void update(float dt);
    };
}

#endif // MONOMI_GAME_HPP
