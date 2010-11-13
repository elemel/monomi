#ifndef MONOMI_WINDOW_HPP
#define MONOMI_WINDOW_HPP

#include <memory>
#include <vector>

struct SDL_Surface;

namespace monomi {
    class Screen;

    class Window {
    public:
        Window();
        ~Window();

        Screen *topScreen();
        const Screen *topScreen() const;

        void pushScreen(std::auto_ptr<Screen> screen);
        void run();
    
    private:
        SDL_Surface *videoSurface_;
        std::vector<Screen *> screens_;

        void handleEvents();
        void popAllScreens();
        void popDeadScreens();
    };
}

#endif // MONOMI_WINDOW_HPP
