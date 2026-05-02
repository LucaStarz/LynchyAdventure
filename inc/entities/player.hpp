#pragma once

#include "entities/entity.hpp"
#include "entities/weapon.hpp"
#include "components/animator.hpp"
#include "utils/spritesheets.hpp"

namespace entities {
    class Player : public Entity {
    public:
        Player();
        ~Player();

        bool update(Zone *container) override;
        void render(float depth, Zone *container) override;

        components::Hurtbox *getHurtbox() const override;
        components::Collider *getCollider() const override;
        components::LifeManager *getLifeManager() const override;
        components::Movement *getMovement() const override;
        components::Animator *getAnimator() const override;

        void checkPlayerOutOfScreen();

        void setLifeInfos(u8 life, u8 max_life);
        void getLifeInfos(u8 *life, u8 *max_life);
    
        void setWeapon(utils::SPRITESHEETS_ID weapon_id);
        utils::SPRITESHEETS_ID getWeaponId() const;
    private:
        Weapon *weapon;

        components::LifeManager *life_manager;
        components::Animator *animator;
        components::Collider *collider;
        components::Hurtbox *hurtbox;
        components::Movement *movement;

        void addAnimations();
    };
}