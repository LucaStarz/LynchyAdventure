#pragma once

#include <3ds.h>

namespace utils {
    enum MOVEMENT_DIRECTION : u8 {
        MOV_DIR_NONE =          0,

        MOV_DIR_LEFT =          BIT(0),
        MOV_DIR_RIGHT =         BIT(1),
        MOV_DIR_TOP =           BIT(2),
        MOV_DIR_BOTTOM =        BIT(3)
    };

    enum FIXED_DIRECTION : u8 {
        FIX_DIR_BOTTOM =    0,
        FIX_DIR_LEFT =      1,
        FIX_DIR_RIGHT =     2,
        FIX_DIR_TOP =       3
    };
}