#include "character_actor.hpp"

#include "character_physics_component.hpp"
#include "character_type.hpp"
#include "debug_graphics.hpp"
#include "game.hpp"
#include "state_machine.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterActor::CharacterActor(Game *game, boost::shared_ptr<CharacterType const> const &type) :
        game(game),
        type(type),
        techniques(type->techniques),
        tools(type->tools),
        alive_(true),
        face(1),
        gravity(0.0f, -20.0f),
        touchLeft(false),
        touchRight(false),
        touchDown(false),
        touchUp(false),
        airJumpCount(0)
    { }

    bool CharacterActor::wallSliding() const
    {
        return (techniques.test(wallSlideTechnique) &&
                tools.test(tigerClawTool) && (touchLeft || touchRight));
    }

    Circle CharacterActor::bottomCircle() const
    {
        return Circle(position -
                      Vector2(0.0f, 0.5f * (type->height - type->width)),
                      0.5f * type->width);
    }

    Circle CharacterActor::topCircle() const
    {
        return Circle(position +
                      Vector2(0.0f, 0.5f * (type->height - type->width)),
                      0.5f * type->width);
    }

    boost::shared_ptr<Component> CharacterActor::physicsComponent()
    {
        return physicsComponent_;
    }

    bool CharacterActor::alive() const
    {
        return true;
    }

    void CharacterActor::update(float dt)
    {
        if (stateMachine_) {
            stateMachine_->update(dt);
        }

        // Copy controls.
        oldControls = controls;
    }

    void CharacterActor::handleCollisions()
    {
        boost::shared_ptr<CharacterActor> playerCharacter =
            boost::dynamic_pointer_cast<CharacterActor>(game->actors_.front());
        if (playerCharacter.get() == this) {
            typedef std::vector<boost::shared_ptr<Actor> >::iterator
                ActorIterator;
            for (ActorIterator i = game->actors_.begin() + 1;
                 i != game->actors_.end(); ++i)
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

    void CharacterActor::debugDraw(DebugGraphics *debugGraphics)
    {
        DebugColor color = debugColors::white();
        if (alive_) {
            if (touchDown) {
                color = debugColors::yellow();
            } else if (wallSliding()) {
                color = debugColors::red();
            } else {
                color = debugColors::lightBlue();
            }
        }
        debugGraphics->drawCircle(bottomCircle(), color);
        debugGraphics->drawCircle(topCircle(), color);
        Circle c = topCircle();
        LineSegment2 s(c.center,
                       c.center + Vector2(float(face) * c.radius, 0.0f));
        debugGraphics->drawLineSegment(s, color);
    }
}
