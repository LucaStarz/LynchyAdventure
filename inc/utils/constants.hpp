#pragma once

namespace utils {
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
    #define SFX_PATH                    "romfs:/sfx/sounds/%u.wav"
    #define CONFIG_SAVE_PATH            "sdmc:/lynchy_adv/config.ldf"
    #define PLAYER_SAVE_PATH            "sdmc:/lynchy_adv/saves/player.ldf"


    /* Default player values */
    #define DEFAULT_PLAYER_POS_X        16.f
    #define DEFAULT_PLAYER_POS_Y        16.f
    #define DEFAULT_PLAYER_ZONE_ID      1
    #define DEFAULT_PLAYER_LIFE         3
    #define DEFAULT_PLAYER_MAX_LIFE     9
    #define DEFAULT_PLAYER_SPEED        .9f
    #define DEFAULT_PLAYER_INV_TIME     90
    #define DEFAULT_PLAYER_WEAPON       20
    #define DEFAULT_PLAYER_COINS        0


    /* Enemies' speed ratio */
    #define ENEMY_BAMBOO_SPEED          .6f
    #define ENEMY_SLIME_SPEED           .7f

    /* Enemies' invicible time */
    #define ENEMY_SLIME_INV_TIME        50


    /* Other constants */
    #define MOVEMENT_DEADZONE           0.1f
    #define ZONE_MOVEMENT_X             6.f
    #define ZONE_MOVEMENT_Y             4.f
    #define MAX_COINS                   999999
}