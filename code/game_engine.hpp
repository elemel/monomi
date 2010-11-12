#ifndef MONOMI_GAME_ENGINE_HPP
#define MONOMI_GAME_ENGINE_HPP

#include <vector>

namespace monomi {
    class Actor;

    class GameEngine {
    public:
        GameEngine();

        void step(float dt);
    
    private:
        float time_;
        std::vector<Actor *> actors_;
    };
}

#endif // MONOMI_GAME_ENGINE_HPP
