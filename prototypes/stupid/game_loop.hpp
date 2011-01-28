#ifndef MONOMI_GAME_LOOP
#define MONOMI_GAME_LOOP

namespace monomi {
    class GameLoop {
    public:
        GameLoop();

        void run();

    private:
        bool quit_;

        void handleInput();
        void updateLogic();
        void updateView();
    };
}

#endif // MONOMI_GAME_LOOP
