#pragma once

#include "entities/weapon.hpp"

namespace entities {
    class Player : public Entity {
    public:
        Player();
        ~Player();

        void update(Zone *container) override;
        void render(float depth, Zone *container) override;

        void checkPlayerOutOfScreen(float dx, float dy);

        void setLifeInfos(u8 life, u8 max_life);
        void getLifeInfos(u8 *life, u8 *max_life);
        void takeDamage();
    
    private:
        Weapon *weapon;
    };
}