#pragma once

#include "entities/entity.hpp"
#include "components/image.hpp"

namespace entities {
    class Heart : public Entity {
    public:
        Heart(float x, float y);
        ~Heart();

        bool update(Zone *container) override;
        void render(float depth, Zone *container) override;
    private:
        components::ImageComponent *image;
        components::Collider *detector;
    };
}