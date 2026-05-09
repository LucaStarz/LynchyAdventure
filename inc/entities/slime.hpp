#pragma once

#include "entities/entity.hpp"
#include "components/hitbox.hpp"
#include "components/squared_detector.hpp"

namespace entities {
    class Slime : public Entity {
    public:
        Slime(float x, float y);
        ~Slime();

        bool update(Zone *container) override;
        void render(float depth, Zone *container) override;
        Entity *getLoot() const override;

        components::Hurtbox *getHurtbox() const override;
        components::Collider *getCollider() const override;
        components::LifeManager *getLifeManager() const override;
        components::Movement *getMovement() const override;
        components::Animator *getAnimator() const override;
    private:
        components::SquaredDetector *dectector;
        components::Animator *animator;
        components::Hurtbox *hurtbox;
        components::Hitbox *hitbox;
        components::Collider *collider;
        components::LifeManager *life_manager;
        components::Movement *movement;

        void addAnimations();
    };
}