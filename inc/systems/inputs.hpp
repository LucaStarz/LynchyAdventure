#pragma once

#include <3ds.h>

namespace systems {
    class InputsSystem final {
    public:
        static InputsSystem &getInstance();

        InputsSystem(const InputsSystem &) = delete;
        InputsSystem &operator=(const InputsSystem &) = delete;

        void update();

        bool isKeyHeld(u32 key) const;
        bool isKeyDown(u32 key) const;
        bool isKeyUp(u32 key) const;

        touchPosition *getTouchPosition();
    private:
        u32 held, down, up;
        touchPosition mouse_position;

        InputsSystem();
        ~InputsSystem();
    };
}