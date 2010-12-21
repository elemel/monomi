#include "character_actor.hpp"

#include "character_physics_component.hpp"
#include "character_type.hpp"
#include "debug_graphics.hpp"

#include <cmath>
#include <iostream>

namespace monomi {
    CharacterActor::CharacterActor(boost::shared_ptr<CharacterType const> const &type) :
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

    boost::shared_ptr<Component> CharacterActor::stateComponent()
    {
        return stateComponent_;
    }

    boost::shared_ptr<Component> CharacterActor::physicsComponent()
    {
        return physicsComponent_;
    }

    boost::shared_ptr<Component> CharacterActor::collisionComponent()
    {
        return collisionComponent_;
    }

    bool CharacterActor::alive() const
    {
        return true;
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
