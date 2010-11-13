#include "game_engine.hpp"
#include "screen.hpp"
#include "sdl_window.hpp"

int main(int argc, char *argv[])
{
    monomi::SDLWindow window;
    std::auto_ptr<monomi::Screen> screen(new monomi::Screen(&window));
    window.pushScreen(screen);
    window.run();
    return 0;
}
