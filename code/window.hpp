#ifndef MONOMI_WINDOW_HPP
#define MONOMI_WINDOW_HPP

namespace monomi {
    class Window {
    public:
        Window(int width, int height);
        virtual ~Window();
    
        virtual void run();
    
        virtual void onResize(int width, int height);
    };
}

#endif // MONOMI_WINDOW_HPP
