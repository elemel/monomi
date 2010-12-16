#include "game_application.hpp"
#include "global_object_registry.hpp"
#include "object_registry.hpp"

#include <SDL.h>

using namespace monomi;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);

    ObjectRegistryPtr objectRegistry(new ObjectRegistry);
    globalObjectRegistry = objectRegistry.get();
    GameApplicationPtr gameApplication(new GameApplication);
    gameApplication->run();
    return 0;
}
