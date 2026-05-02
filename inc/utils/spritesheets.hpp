#pragma once

#include <3ds.h>

namespace utils {
    enum SPRITESHEETS_ID : u16 {
        SPRT_EMPTY = 0,
        SPRT_END_OF_LINE = 1,

        SPRT_GREEN_FLOOR = 2,
        SPRT_PLANT = 3,
        SPRT_GREEN_WATER = 4,
        SPRT_DARK_MILL = 5,
        SPRT_BLACK_FLAG = 6,
        SPRT_PLAYER_LEFT = 7,
        SPRT_PLAYER_TOP = 8,
        SPRT_PLAYER_RIGHT = 9,
        SPRT_PLAYER_BOTTOM = 10,
        SPRT_LIGHT_MILL = 11,
        SPRT_SIMPLE_HOUSE = 12,
        SPRT_WOOD_FENCE = 13,
        SPRT_GREEN_BAMBOO_LEFT = 14,
        SPRT_GREEN_BAMBOO_TOP = 15,
        SPRT_GREEN_BAMBOO_RIGHT = 16,
        SPRT_GREEN_BAMBOO_BOTTOM = 17,
        SPRT_LIFE_RECEPTACLE = 18,
        SPRT_WEAPON_AXE = 19,
        SPRT_WEAPON_STICK = 20,
        SPRT_DEAD = 21,
        SPRT_COIN = 22
    };
}