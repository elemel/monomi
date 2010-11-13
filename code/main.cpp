#include "game_engine.hpp"
#include "screen.hpp"
#include "window.hpp"

int main(int argc, char *argv[])
{
    monomi::Window window;
    std::auto_ptr<monomi::Screen> screen(new monomi::Screen(&window));
    window.pushScreen(screen);
    window.run();
    return 0;
}
