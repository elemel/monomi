#ifndef MONOMI_GAME_ENGINE_HPP
#define MONOMI_GAME_ENGINE_HPP

#include <boost/ptr_container/ptr_vector.hpp>

namespace monomi {
    class Actor;

    class GameEngine {
    public:
        GameEngine();
        ~GameEngine();

        void addActor(std::auto_ptr<Actor> actor);
        void step(float dt);
        void draw() const;

    private:
        float time_;
        boost::ptr_vector<Actor> actors_;
    };
}

#endif // MONOMI_GAME_ENGINE_HPP
