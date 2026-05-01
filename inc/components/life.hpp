#pragma once

#include "components/timer.hpp"
#include <3ds.h>

namespace components {
    class LifeManager : public Component {
    public:
        LifeManager(u8 life, u8 max_life, u16 invicible_time);
        ~LifeManager();

        void update(entities::Entity *parent, entities::Zone *container) override;

        u8 getActualLife() const;
        void setActualLife(u8 life);

        u8 getMaxLife() const;
        void setMaxLife(u8 max_life);
        
        void takeDamage(u8 damage);
        void addLife(u8 life);

        bool isDead() const;
    private:
        u8 actual_life, max_life;

        Timer *timer;
    };
}