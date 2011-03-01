#include "character_config_loader.hpp"
#include "character_type.hpp"
#include "color.hpp"
#include "game_logic.hpp"
#include "game_loop.hpp"
#include "level_loader.hpp"
#include "string_buffer.hpp"
#include "svg_parser.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <SDL.h>
#include <boost/timer.hpp>

using namespace monomi;

int main(int argc, char *argv[])
{
    try {
        boost::timer t1;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
            throw std::runtime_error(StringBuffer() <<
                                     "Failed to initialize SDL: " <<
                                     SDL_GetError());
        }

        if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1) {
            std::cerr << "WARNING: Failed to enable double buffering: "
                      << SDL_GetError() << std::endl;
        }
        SDL_Surface *videoSurface = SDL_SetVideoMode(0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN);
        if (videoSurface == 0) {
            throw std::runtime_error(StringBuffer() <<
                                     "Failed to set SDL video mode: " <<
                                     SDL_GetError());
        }
        if (SDL_GL_SetSwapInterval(1) == -1) {
            std::cerr << "WARNING: Failed to enable vertical sync: "
                      << SDL_GetError() << std::endl;
        }

        std::cerr << "DEBUG: Initialized SDL in " << t1.elapsed() << " second(s)." << std::endl;

        boost::shared_ptr<GameLogic> gameLogic(new GameLogic);

        std::string assetsDir = (argc == 2) ? argv[1] : ".";

        CharacterConfigLoader(*gameLogic).load(assetsDir + "/config/character.ini");

        std::string characterName = "grandmaster";
        if (gameLogic->findCharacterType(characterName)) {
            gameLogic->playerCharacterName(characterName);
        } else {
            std::cerr << "WARNING: Invalid character name \"" << characterName
                      << "\"." << std::endl;
        }

        boost::timer t2;

        std::string levelPath = assetsDir + "/levels/sandbox.svg";
        LevelLoader(*gameLogic).load(levelPath);

        gameLogic->createCharacter("samurai", Vector2(7.0f, 0.0f), ENEMY_CATEGORY);

        GameLoop gameLoop(gameLogic);
        gameLoop.run();
    } catch (std::exception const &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    SDL_Quit();
    return 0;
}
