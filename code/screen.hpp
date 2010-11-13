#ifndef MONOMI_SCREEN_HPP
#define MONOMI_SCREEN_HPP

namespace monomi {
    class Window;

    class Screen {
    public:
        explicit Screen(Window *window);
        virtual ~Screen();

        bool alive() const;

        virtual void open();
        virtual void suspend();
        virtual void resume();
        virtual void close();
    
        virtual void update();
        virtual void draw() const;

    protected:
        Window *window_;
        bool alive_;
    };
}

#endif // MONOMI_SCREEN_HPP
