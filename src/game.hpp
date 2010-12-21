#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace monomi {
    class Actor;
    class CharacterFactory;
    class Random;

    class Game {
    public:
        float time_;
        boost::shared_ptr<Random> random_;
        std::vector<boost::shared_ptr<Actor> > actors_;

        boost::shared_ptr<CharacterFactory> characterFactory_;

        Game();

        void addActor(boost::shared_ptr<Actor> const &actor);

        void update(float dt);

    private:
        std::vector<boost::shared_ptr<Actor> > newActors_;

        void addNewActors();
        void removeDeadActors();
    };
}

#endif // MONOMI_GAME_HPP
