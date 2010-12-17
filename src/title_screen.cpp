#include "title_screen.hpp"

#include "game_screen.hpp"

#include <GL/gl.h>

namespace monomi {
    TitleScreen::TitleScreen() :
        quit_(false)
    { }

    boost::shared_ptr<Screen> TitleScreen::run()
    {
        do {
            pollEvents();
            draw();
        } while (!quit_);
        return boost::shared_ptr<Screen>();
    }

    void TitleScreen::pollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                onKeyDown(event);
                break;

            case SDL_KEYUP:
                break;

            case SDL_QUIT:
                quit_ = true;
                break;
            }
        }
    }

    void TitleScreen::onKeyDown(const SDL_Event &event)
    {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            quit_ = true;
            break;

        case SDLK_SPACE:
        case SDLK_RETURN:
            boost::shared_ptr<GameScreen> gameScreen(new GameScreen);
            gameScreen->run();
            break;
        }
    }

    void TitleScreen::draw()
    {
        glClearColor(1.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        SDL_GL_SwapBuffers();
    }
}
