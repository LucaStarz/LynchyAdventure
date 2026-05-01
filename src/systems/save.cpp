#include "systems/save.hpp"
#include <cstdio>
#include "utils/constants.hpp"
#include "utils/utilities.hpp"
#include "systems/game.hpp"
#include "systems/zone_system.hpp"

using namespace systems;

SaveSystem &SaveSystem::getInstance() {
    static SaveSystem instance;
    return instance;
}

SaveSystem::SaveSystem() {
    romfsInit();
    this->createDirectory("/lynchy_adv");
    this->createDirectory("/lynchy_adv/saves");
}

SaveSystem::~SaveSystem() {
    romfsExit();
}

void SaveSystem::loadConfigurations() {
    FILE *config_file = fopen(CONFIG_SAVE_PATH, "rb");
    if (!config_file) {
        this->initConfigurations();
        return;
    }

    // Read game's language
    this->lang = fgetc(config_file);

    PRINT("Configs has been read\n");
    fclose(config_file);
}

void SaveSystem::loadPlayerSave() {
    FILE *player_save_file = fopen(PLAYER_SAVE_PATH, "rb");
    if (!player_save_file) {
        this->initPlayerSave();
        return;
    }

    GameSystem &game_system = GameSystem::getInstance();
    ZoneSystem &zone_system = ZoneSystem::getInstance();

    // Read player's coord
    float x, y;
    fread(&x, sizeof(float), 1, player_save_file);
    fread(&y, sizeof(float), 1, player_save_file);
    game_system.getPlayer()->setX(x);
    game_system.getPlayer()->setY(y);

    u16 zone_id;
    fread(&zone_id, sizeof(u16), 1, player_save_file);
    zone_system.load(zone_id);

    // Read player's life
    u8 actual_life = fgetc(player_save_file);
    u8 max_life = fgetc(player_save_file);
    game_system.getPlayer()->setLifeInfos(actual_life, max_life);

    // Read player's weapon id
    u16 weapon_id;
    fread(&weapon_id, sizeof(u16), 1, player_save_file);
    game_system.getPlayer()->setWeapon(weapon_id);

    PRINT("Player's data has been read\n");
    fclose(player_save_file);
}

void SaveSystem::storePlayerSave() {
    FILE *player_save_file = fopen(PLAYER_SAVE_PATH, "wb");
    if (!player_save_file) {
        PRINT("Failed to store data in player's savefile\n");
        return;
    }

    GameSystem &game_system = GameSystem::getInstance();
    ZoneSystem &zone_system = ZoneSystem::getInstance();
    
    // Store player's coord
    float x = game_system.getPlayer()->getX();
    float y = game_system.getPlayer()->getY();
    fwrite(&x, sizeof(float), 1, player_save_file);
    fwrite(&y, sizeof(float), 1, player_save_file);

    u16 zone_id = zone_system.getActualZoneId();
    fwrite(&zone_id, sizeof(u16), 1, player_save_file);

    // Store player's life
    u8 life, max_life;
    game_system.getPlayer()->getLifeInfos(&life, &max_life);
    fputc(life, player_save_file);
    fputc(max_life, player_save_file);

    // Store player's weapon id
    u16 weapon_id = game_system.getPlayer()->getWeaponId();
    fwrite(&weapon_id, sizeof(u16), 1, player_save_file);

    PRINT("Player's data has been saved\n");
    fclose(player_save_file);
}

void SaveSystem::loadWeaponData(entities::Weapon *weapon, u16 weapon_id) {
    char weapon_path[64];
    sprintf(weapon_path, "romfs:/weapons/%u.wdf", weapon_id);
    FILE *weapon_data_file = fopen(weapon_path, "rb");
    if (!weapon_data_file) {
        PRINT("Failed to open weapon data file %u\n", weapon_id);
        return;
    }

    weapon->setSpritesheet(weapon_id);

    u16 duration;
    fread(&duration, sizeof(u16), 1, weapon_data_file);
    weapon->setDuration(duration);

    weapon->setDamage(fgetc(weapon_data_file));

    for (u8 i = utils::FIX_DIR_BOTTOM; i <= utils::FIX_DIR_TOP; i++) {
        s16 offset_x, offset_y;
        u16 width, height;
        fread(&offset_x, sizeof(s16), 1, weapon_data_file);
        fread(&offset_y, sizeof(s16), 1, weapon_data_file);
        fread(&width, sizeof(u16), 1, weapon_data_file);
        fread(&height, sizeof(u16), 1, weapon_data_file);

        weapon->setDirectionInfo(i, offset_x, offset_y, width, height);
    }

    PRINT("Weapon's data %u was loaded\n", weapon_id);
    fclose(weapon_data_file);
}

u8 SaveSystem::getLang() const {
    return this->lang;
}

void SaveSystem::initConfigurations() {
    FILE *config_file = fopen(CONFIG_SAVE_PATH, "wb");
    if (!config_file) {
        PRINT("Failed to initialize config file\n");
        return;
    }
    
    // Initialize game's language
    CFGU_GetSystemLanguage(&this->lang);
    fputc(this->lang, config_file);
    
    fclose(config_file);
}

void SaveSystem::initPlayerSave() {
    FILE *player_save_file = fopen(PLAYER_SAVE_PATH, "wb");
    if (!player_save_file) {
        PRINT("Failed to initialize player's savefile\n");
        return;
    }

    GameSystem &game_system = GameSystem::getInstance();
    ZoneSystem &zone_system = ZoneSystem::getInstance();
    
    // Initialize player's coord
    game_system.getPlayer()->setX(DEFAULT_PLAYER_POS_X);
    game_system.getPlayer()->setY(DEFAULT_PLAYER_POS_Y);
    float x = game_system.getPlayer()->getX();
    float y = game_system.getPlayer()->getY();
    fwrite(&x, sizeof(float), 1, player_save_file);
    fwrite(&y, sizeof(float), 1, player_save_file);

    zone_system.load(DEFAULT_PLAYER_ZONE_ID);
    u16 zone_id = zone_system.getActualZoneId();
    fwrite(&zone_id, sizeof(u16), 1, player_save_file);

    // Initialize player's life
    u8 life = DEFAULT_PLAYER_LIFE, max_life = DEFAULT_PLAYER_MAX_LIFE;
    game_system.getPlayer()->setLifeInfos(life, max_life);
    fputc(life, player_save_file);
    fputc(max_life, player_save_file);

    // Initialize player's weapon id
    u16 weapon_id = DEFAULT_PLAYER_WEAPON;
    game_system.getPlayer()->setWeapon(weapon_id);
    fwrite(&weapon_id, sizeof(u16), 1, player_save_file);

    fclose(player_save_file);
}

void SaveSystem::createDirectory(const char *directory) {
    FS_Archive sdmc;
    Result rc = FSUSER_OpenArchive(&sdmc, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
    if (R_FAILED(rc)) {
        PRINT("Failed to create directory manager\n");
        return;
    }

    FSUSER_CreateDirectory(sdmc, fsMakePath(PATH_ASCII, directory), 0);
    FSUSER_CloseArchive(sdmc);
}