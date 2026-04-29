#pragma once

#include "base.hpp"

namespace entities {
    class Entity;
    class Zone;
}

namespace systems {
    class GameSystem;
}

namespace components {
    class Component {
    public:
        virtual ~Component();

        virtual void update(entities::Entity *parent, entities::Zone *container);
        virtual void render(entities::Entity *parent, float depth, entities::Zone *container);
    protected:
        Component();
    };
}