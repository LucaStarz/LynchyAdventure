#pragma once

/* Imports */
#include <3ds.h>
#include <citro2d.h>

#include <array>
#include <unordered_map>
#include <vector>


/* Screen informations */
#define ZONE_WIDTH                  25
#define ZONE_HEIGHT                 15
#define TILE_SIZE                   16.f
#define SCREEN_WIDTH                400.f
#define SCREEN_HEIGHT               240.f


/* Z index priority */
#define Z_INDEX_BACKGROUND          0.f
#define Z_INDEX_MORE_BACKGROUND     0.2f
#define Z_INDEX_PLAYER              0.4f
#define Z_INDEX_FOREGROUND          0.6f
#define Z_INDEX_MORE_FOREGROUND     0.8f
#define Z_INDEX_UI                  1.f


/* Filepaths */
#define FONT_PATH                   "romfs:/gfx/font.bcfnt"
#define GFX_PATH                    "romfs:/gfx/%u.t3x"
#define TEXT_PATH                   "romfs:/texts/%u/%u.ltf"
#define CONFIG_SAVE_PATH            "sdmc:/lynchy_adv/config.ldf"
#define PLAYER_SAVE_PATH            "sdmc:/lynchy_adv/saves/player.ldf"


/* Default player values */
#define DEFAULT_PLAYER_POS_X        16.f
#define DEFAULT_PLAYER_POS_Y        16.f
#define DEFAULT_PLAYER_ZONE_ID      1
#define DEFAULT_PLAYER_LIFE         3
#define DEFAULT_PLAYER_MAX_LIFE     9
#define DEFAULT_PLAYER_SPEED        .9f
#define DEFAULT_PLAYER_INV_TIME     120
#define DEFAULT_PLAYER_WEAPON_TIME  120
#define DEFAULT_PLAYER_WEAPON_SPR   20


/* Enemies' speed ratio */
#define ENEMY_BAMBOO_SP_RT          1.75f


/* Debug data */
#ifdef LYNCHY_DEBUG
    #define DEBUG_COLLIDER_COLOR()  C2D_Color32(100, 227, 209, 125)
    #define DEBUG_HITBOX_COLOR()    C2D_Color32(242, 121, 94, 125)
    #define DEBUG_HURTBOX_COLOR()   C2D_Color32(129, 230, 103, 125)
    #define DEBUG_SQR_DET_COLOR()   C2D_Color32(232, 165, 227, 125)

    #define PRINT(fmt, ...)         printf(fmt, ##__VA_ARGS__)
#else
    #define PRINT(fmt, ...)         ((void)0)
#endif


/* Spritesheets */
enum SP_SPRITESHEETS : u16 {
    // Player's spritesheets
    SPRT_PLAYER_LEFT = 7,
    SPRT_PLAYER_TOP,
    SPRT_PLAYER_RIGHT,
    SPRT_PLAYER_BOTTOM,

    // Green bamboo's spritesheets
    SPRT_GREEN_BAMBOO_LEFT = 14,
    SPRT_GREEN_BAMBOO_TOP,
    SPRT_GREEN_BAMBOO_RIGHT,
    SPRT_GREEN_BAMBOO_BOTTOM,

    // Weapons' spritesheets
    SPRT_WEAPON_AXE = 19,
    SPRT_WEAPON_STICK
};


/* Other constants */
#define MOVEMENT_DEADZONE           0.1f
#define ZONE_MOVEMENT_X             5.f
#define ZONE_MOVEMENT_Y             3.5f


/* Simple functions */
#define MAX(a, b)                   (((a) > (b)) ? (a) : (b))
#define MIN(a, b)                   (((a) < (b)) ? (a) : (b))


/* Components' id */
enum COMPONENT_ID : u8 {
    // Image or animated-image
    COMP_IMAGE =            0b00000000,

    COMP_COLLIDER =         0b00000001,
    COMP_HITBOX =           0b00000010,
    COMP_HURTBOX =          0b00000011,
    COMP_LIFE =             0b00000100,
    COMP_MOVEMENT =         0b00000101,
    COMP_SQUARED_DETECTOR = 0b00000110,
    COMP_TIMER =            0b00000111,
    MAX_COMPONENT,
};


/* Collisions' mask */
enum COLLISION_LAYER : u8 {
    COL_LAYER_NONE =        0,

    COL_LAYER_PLAYER =      BIT(0),
    COL_LAYER_TERRAIN =     BIT(1),
    COL_LAYER_ENEMY =       BIT(2),
    COL_LAYER_WATER =       BIT(3),
    COL_LAYER_PLAYER_PROJ = BIT(4),
    COL_LAYER_ENEMY_PROJ =  BIT(5)
};


/* Directions */
enum MOVEMENT_DIRECTION : u8 {
    MOV_DIR_NONE =          0,

    MOV_DIR_LEFT =          BIT(0),
    MOV_DIR_RIGHT =         BIT(1),
    MOV_DIR_TOP =           BIT(2),
    MOV_DIR_BOTTOM =        BIT(3)
};