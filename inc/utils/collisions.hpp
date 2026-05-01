#pragma once

#include <3ds.h>

namespace utils {
    enum COLLISION_LAYER : u8 {
        COL_LAYER_NONE =        0,

        COL_LAYER_PLAYER =      BIT(0),
        COL_LAYER_TERRAIN =     BIT(1),
        COL_LAYER_ENEMY =       BIT(2),
        COL_LAYER_WATER =       BIT(3),
        COL_LAYER_PLAYER_PROJ = BIT(4),
        COL_LAYER_ENEMY_PROJ =  BIT(5)
    };
}