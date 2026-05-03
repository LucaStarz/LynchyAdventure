#pragma once

#include "entities/entity.hpp"
#include "components/animated_image.hpp"

namespace entities {
    class Coin : public Entity {
    public:
        Coin(float x, float y);
        ~Coin();

        bool update(Zone *container) override;
        void render(float depth, Zone *container) override;
    private:
        components::AnimatedImage *image;
        components::Collider *detector;
    };
}