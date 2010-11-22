#include "game_screen.hpp"

#include "game_engine.hpp"
#include "character_actor.hpp"
#include "level_actor.hpp"
#include "window.hpp"

#include <fstream>
#include <iostream>
#include <GL/gl.h>

namespace monomi {
    GameScreen::GameScreen(Window *window) :
        window_(window),
        alive_(true)
    {
        gameEngine_.reset(new GameEngine(window_->width(), window_->height()));
        gameEngine_->addActor(createLevelActor("level.txt"));
        gameEngine_->addActor(createCharacterActor());
    }

    bool GameScreen::alive()
    {
        return alive_;
    }

    void GameScreen::update()
    { }

    void GameScreen::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        gameEngine_->debugDraw();
    }

    void GameScreen::onOpen()
    { }

    void GameScreen::onSuspend()
    { }

    void GameScreen::onResume()
    { }

    void GameScreen::onClose()
    { }

    void GameScreen::onKeyPress(Key key, Modifiers modifiers)
    {
        alive_ = false;
    }

    void GameScreen::onKeyRelease(Key key, Modifiers modifiers)
    { }

    std::auto_ptr<Actor> GameScreen::createLevelActor(const std::string &fileName)
    {
        std::ifstream in(fileName.c_str());
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(in, line)) {
            lines.push_back(line);
        }
        std::auto_ptr<LevelActor> levelActor(new LevelActor(gameEngine_.get(), lines));
        return std::auto_ptr<Actor>(levelActor);
    }

    std::auto_ptr<Actor> GameScreen::createCharacterActor()
    {
        std::auto_ptr<CharacterActor> characterActor(new CharacterActor(gameEngine_.get()));
        return std::auto_ptr<Actor>(characterActor);
    }
}
