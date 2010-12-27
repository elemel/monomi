#ifndef MONOMI_GAME_HPP
#define MONOMI_GAME_HPP

#include "actor_fwd.hpp"

#include <vector>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class CharacterFactory;

    // The hub of the game logic.
    class Game {
    public:
        typedef std::vector<ActorPtr> ActorVector;

        Game();

        float time() const;

        ActorVector &actors();
        ActorVector const &actors() const;

        // Add an actor to the game. The actor will actually be added during
        // the next update.
        void addActor(ActorPtr const &actor);

        // Update the game state.
        void update(float dt);

    private:
        float time_;
        boost::shared_ptr<CharacterFactory> characterFactory_;
        ActorVector newActors_;
        ActorVector actors_;

        void addNewActors();
        void removeDeadActors();
    };
}

#endif // MONOMI_GAME_HPP
