#pragma once

#include "systems/gfx.hpp"

namespace systems {
    class CameraSystem {
    public:
        static CameraSystem &getInstance();

        CameraSystem(const CameraSystem&) = delete;
        CameraSystem &operator=(const CameraSystem&) = delete;

        void setLimitX(float x);
        void setLimitY(float y);

        float getX() const;
        float getY() const;
        void setX(float x);
        void setY(float y);
    private:
        float limit_x, limit_y;
        float x, y;

        CameraSystem();
        ~CameraSystem();
    };
}