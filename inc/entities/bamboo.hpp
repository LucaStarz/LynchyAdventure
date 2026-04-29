#pragma once

#include "entities/collision.hpp"

namespace entities {
    class Bamboo : public Entity {
    public:
        Bamboo(float x, float y);
        ~Bamboo();

        void update(Zone *container) override;
        void render(float depth, Zone *container) override;
    private:
    };
}