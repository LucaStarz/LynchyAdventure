#pragma once

#include "components/collider.hpp"

namespace components {
    class LifeManager : public Component {
    public:
        LifeManager(u8 life, u8 max_life);
        ~LifeManager();

        u8 getActualLife() const;
        void setActualLife(u8 life);

        u8 getMaxLife() const;
        void setMaxLife(u8 max_life);
        
        void takeDamage(u8 damage);
        void addLife(u8 life);

        bool isInvicible() const;
        void setInvicible(u8 invicible_time);
    private:
        u8 actual_life, max_life;
        u8 invicible_time;
    };
}