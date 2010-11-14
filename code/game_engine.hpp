#ifndef MONOMI_GAME_ENGINE_HPP
#define MONOMI_GAME_ENGINE_HPP

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace monomi {
    class Actor;

    class GameEngine :
        private boost::noncopyable
    {
    public:
        GameEngine(int screenWidth, int screenHeight);
        ~GameEngine();

        void addActor(std::auto_ptr<Actor> actor);
        void step(float dt);
        void draw();
        void debugDraw();

    private:
        int screenWidth_, screenHeight_;
        float time_;
        boost::ptr_vector<Actor> actors_;
    };
}

#endif // MONOMI_GAME_ENGINE_HPP
