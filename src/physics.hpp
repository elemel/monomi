#ifndef MONOMI_PHYSICS_HPP
#define MONOMI_PHYSICS_HPP

namespace monomi {
    class CharacterActor;
    class Game;

    class Physics {
    public:
        explicit Physics(Game *game);

        void update(float dt);

    private:
        Game *game_;

        void applyConstraints();
        void updateTouchFlags(CharacterActor *character);
        void resolveCollisions();
    };
}

#endif // MONOMI_PHYSICS_HPP
