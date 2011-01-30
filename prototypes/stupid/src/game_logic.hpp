#ifndef MONOMI_GAME_LOGIC_HPP
#define MONOMI_GAME_LOGIC_HPP

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <Box2D/Dynamics/b2World.h>

namespace monomi {
    class DebugGraphics;

    class GameLogic : private boost::noncopyable {
    public:
        GameLogic();
        void update(float dt);
        void debugDraw(DebugGraphics *graphics);

    private:
        float time_;
        boost::shared_ptr<b2World> world_;
    };
}

#endif // MONOMI_GAME_LOGIC_HPP
