#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include <vector>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class Actor;
    class CharacterFactory;

    // The hub of the game logic.
    class Game {
    public:
        Game();

        float time() const;

        std::vector<boost::shared_ptr<Actor> > &actors();
        std::vector<boost::shared_ptr<Actor> > const &actors() const;

        // Add an actor to the game. The actor will actually be added during
        // the next update.
        void addActor(boost::shared_ptr<Actor> const &actor);

        // Update the game state.
        void update(float dt);

    private:
        float time_;
        boost::shared_ptr<CharacterFactory> characterFactory_;
        std::vector<boost::shared_ptr<Actor> > newActors_;
        std::vector<boost::shared_ptr<Actor> > actors_;

        void addNewActors();
        void removeDeadActors();
    };
}

#endif // MONOMI_GAME_HPP
