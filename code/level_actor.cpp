#include "level_actor.hpp"

#include "debug_graphics.hpp"
#include "geometry.hpp"

#include <iostream>

namespace monomi {
    LevelActor::LevelActor(GameEngine *gameEngine,
                           const std::vector<std::string> &lines) :
        gameEngine_(gameEngine)
    {
        for (std::vector<std::string>::const_iterator i = lines.begin();
             i != lines.end();
             ++i)
         {
             tiles_.push_back(std::vector<char>(i->begin(), i->end()));
         }
    }

    bool LevelActor::alive()
    {
        return true;
    }

    void LevelActor::step(float dt)
    { }

    void LevelActor::debugDraw(DebugGraphics *debugGraphics)
    {
        for (std::size_t y = 0; y < tiles_.size(); ++y) {
            const std::vector<char> &row = tiles_[y];
            for (std::size_t x = 0; x < row.size(); ++x) {
                if (tiles_[y][x] != ' ') {
                    Box2 box(Point2(float(x), float(y)),
                             Point2(float(x + 1), float(y + 1)));
                    debugGraphics->drawBox(box);
                }
            }
        }
    }
}
