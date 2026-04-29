#pragma once

#include "components/timer.hpp"

namespace entities {
    class Zone;

    class Entity {
    public:
        virtual ~Entity();

        float getX() const;
        float getY() const;

        void setX(float x);
        void setY(float y);
    
        void moveX(float x);
        void moveY(float y);
        void moveXY(float x, float y);

        void addComponent(components::Component *component, u8 component_id);
        components::Component *getComponent(u8 component_id) const;

        virtual void update(Zone *container);
        virtual void render(float depth, Zone *container);
    protected:
        Entity(float x, float y);
    
    private:
        float x, y;
        std::array<components::Component*, MAX_COMPONENT> entity_components{};
    };
}