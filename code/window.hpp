#ifndef MONOMI_WINDOW_HPP
#define MONOMI_WINDOW_HPP

struct SDL_Surface;

namespace monomi {
    class Window {
    public:
        Window(int width, int height);
        virtual ~Window();
    
        virtual void run();
    
        virtual void onResize(int width, int height);
        virtual void onIdle();
        virtual void onDraw();

    private:
        bool running_;
        SDL_Surface *videoSurface_;

        void handleEvents();
    };
}

#endif // MONOMI_WINDOW_HPP
