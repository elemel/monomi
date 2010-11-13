#include "game_engine.hpp"
#include "window.hpp"

int main(int argc, char *argv[])
{
    monomi::Window window(640, 480);
    window.run();
    return 0;
}
