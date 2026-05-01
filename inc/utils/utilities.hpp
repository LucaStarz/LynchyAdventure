#pragma once

namespace utils {
    #define MAX(a, b)                   (((a) > (b)) ? (a) : (b))
    #define MIN(a, b)                   (((a) < (b)) ? (a) : (b))

    #ifdef LYNCHY_DEBUG
        #define DEBUG_COLLIDER_COLOR()  C2D_Color32(100, 227, 209, 125)
        #define DEBUG_HITBOX_COLOR()    C2D_Color32(242, 121, 94, 125)
        #define DEBUG_HURTBOX_COLOR()   C2D_Color32(129, 230, 103, 125)
        #define DEBUG_SQR_DET_COLOR()   C2D_Color32(232, 165, 227, 125)

        #define PRINT(fmt, ...)         printf(fmt, ##__VA_ARGS__)
    #else
        #define PRINT(fmt, ...)         ((void)0)
    #endif
}