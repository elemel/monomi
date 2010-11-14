#include "game_screen.hpp"
#include "sdl_window.hpp"

int main(int argc, char *argv[])
{
    monomi::SDLWindow window;
    std::auto_ptr<monomi::Screen> screen(new monomi::GameScreen(&window));
    window.pushScreen(screen);
    window.run();
    return 0;
}
