#pragma once

#include "components/collider.hpp"
#include "components/life.hpp"
#include "components/hurtbox.hpp"
#include "components/movement.hpp"
#include "components/animator.hpp"

namespace entities {
    class Zone;

    class Entity {
    public:
        virtual ~Entity();

        float getX() const;
        float getY() const;
        float getWidth() const;
        float getHeight() const;

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
    
        void moveX(float x);
        void moveY(float y);
        void moveXY(float x, float y);

        virtual bool update(Zone *container);
        virtual void render(float depth, Zone *container);
        virtual Entity *getLoot() const;

        virtual components::Hurtbox *getHurtbox() const;
        virtual components::Collider *getCollider() const;
        virtual components::LifeManager *getLifeManager() const;
        virtual components::Movement *getMovement() const;
        virtual components::Animator *getAnimator() const;
    protected:
        Entity(float x, float y, float width, float height);
    
    private:
        float x, y, width, height;
    };
}