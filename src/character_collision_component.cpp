#include "character_collision_component.hpp"

#include "character_actor.hpp"
#include "game.hpp"

#include <boost/shared_ptr.hpp>

namespace monomi {
    CharacterCollisionComponent::CharacterCollisionComponent(CharacterActor *character, Game *game) :
        character_(character),
        game_(game)
    { }

    void CharacterCollisionComponent::update(float dt)
    {
        boost::shared_ptr<CharacterActor> playerCharacter =
            boost::dynamic_pointer_cast<CharacterActor>(game_->actors_.front());
        if (playerCharacter.get() == character_) {
            typedef std::vector<boost::shared_ptr<Actor> >::iterator
                ActorIterator;
            for (ActorIterator i = game_->actors_.begin() + 1;
                 i != game_->actors_.end(); ++i)
            {
                if (boost::shared_ptr<CharacterActor> otherCharacter =
                    boost::dynamic_pointer_cast<CharacterActor>(*i))
                {
                    if (playerCharacter->alive_ && otherCharacter->alive_ &&
                        (intersects(playerCharacter->bottomCircle(),
                                    otherCharacter->bottomCircle()) ||
                         intersects(playerCharacter->bottomCircle(),
                                    otherCharacter->topCircle()) ||
                         intersects(playerCharacter->topCircle(),
                                    otherCharacter->bottomCircle()) ||
                         intersects(playerCharacter->topCircle(),
                                    otherCharacter->topCircle())))
                    {
                        int side = int(sign(otherCharacter->position.x -
                                            playerCharacter->position.x));
                        if (side == otherCharacter->face) {
                            otherCharacter->alive_ = false;
                        } else {
                            playerCharacter->alive_ = false;
                        }
                        playerCharacter->velocity *= 0.5f;
                        otherCharacter->velocity *= 0.5f;
                    }
                }
            }
        }
    }
}
