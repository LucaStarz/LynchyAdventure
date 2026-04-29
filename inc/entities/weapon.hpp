#pragma once

#include "entities/zone.hpp"

namespace entities {
    class Weapon : public Entity {
    public:
        Weapon(float x, float y, float w, float h, u8 damage, u8 scan, u16 duration, u16 spritesheet, u16 sprite_index);
        ~Weapon();
    
        bool isEnable() const;
        void setEnable();

        void update(Zone *container) override;
        void render(float depth, Zone *container) override;
    private:
        bool enable;
    };
}