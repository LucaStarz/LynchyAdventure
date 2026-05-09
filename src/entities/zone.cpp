#include "entities/zone.hpp"
#include "entities/collision.hpp"
#include "entities/bamboo.hpp"
#include "entities/slime.hpp"
#include "entities/tile.hpp"
#include "entities/animated_tile.hpp"
#include "utils/constants.hpp"
#include "utils/utilities.hpp"
#include "utils/spritesheets.hpp"
#include "systems/gfx.hpp"

using namespace entities;

Zone::Zone(float x, float y)
    : Entity(x, y, SCREEN_WIDTH, SCREEN_HEIGHT) {
    
}

Zone::~Zone() {
    this->clear();
}

bool Zone::update(Zone *container) {
    for (Entity *entity : this->background_entities)
        entity->update(this);
    
    for (Entity *entity : this->more_background_entities)
        entity->update(this);
    
    std::vector<Entity*> to_add;
    for (auto it = this->complex_entities.begin(); it != this->complex_entities.end(); ) {
        Entity* entity = *it;
        
        if (!entity->update(this)) {
            Entity* loot = entity->getLoot();
            if (loot)
                to_add.push_back(loot);

            delete entity;
            it = this->complex_entities.erase(it);
        } else {
            ++it;
        }
    }

    this->complex_entities.insert(
        this->complex_entities.end(),
        to_add.begin(),
        to_add.end()
    );
    
    for (Entity *entity : this->foreground_entities)
        entity->update(this);
    
    for (Entity *entity : this->more_foreground_entities)
        entity->update(this);
    
    return true;
}

void Zone::renderBackground() {
    for (Entity *entity : this->background_entities)
        entity->render(Z_INDEX_BACKGROUND, this);
    
    for (Entity *entity : this->more_background_entities)
        entity->render(Z_INDEX_MORE_BACKGROUND, this);
    
    for (Entity *entity : this->complex_entities)
        entity->render(Z_INDEX_PLAYER, this);
}

void Zone::renderForeground() {
    for (Entity *entity : this->foreground_entities)
        entity->render(Z_INDEX_FOREGROUND, this);
    
    for (Entity *entity : this->more_foreground_entities)
        entity->render(Z_INDEX_MORE_FOREGROUND, this);
}

void Zone::load(u16 id, u16 *left, u16 *right, u16 *top, u16 *bottom) {
    this->id = id;
    systems::GraphicsSystem &gfx_system = systems::GraphicsSystem::getInstance();

    for (utils::SPRITESHEETS_ID spritesheet : this->spritesheets)
        gfx_system.unloadSpritesheet(spritesheet);
    this->clear();

    if (!id)
        return;
    
    char filename[96];
    sprintf(filename, "romfs:/zones/%u.zdf", id);

    FILE *zone_file = fopen(filename, "rb");
    if (!zone_file) {
        printf("Failed to locate zone %u\n", id);
        return;
    }

    *left = this->loadU16(zone_file);
    *top = this->loadU16(zone_file);
    *right = this->loadU16(zone_file);
    *bottom = this->loadU16(zone_file);

    utils::SPRITESHEETS_ID spritesheet_id = (utils::SPRITESHEETS_ID)this->loadU16(zone_file);
    while (spritesheet_id) {
        gfx_system.loadSpritesheet(spritesheet_id);
        this->spritesheets.push_back(spritesheet_id);
        spritesheet_id = (utils::SPRITESHEETS_ID)this->loadU16(zone_file);
    }

    this->loadZonePart(&this->background_entities, zone_file);
    this->loadZonePart(&this->more_background_entities, zone_file);
    this->loadZonePart(&this->foreground_entities, zone_file);
    this->loadZonePart(&this->more_foreground_entities, zone_file);
    this->loadZoneCollisions(zone_file);

    PRINT("Zone %u has been loaded\n", this->id);
    fclose(zone_file);
}

void Zone::unload() {
    this->load(0, nullptr, nullptr, nullptr, nullptr);
}

void Zone::getNeighbours(u16 *left, u16 *right, u16 *top, u16 *bottom) {
    char filename[96];
    sprintf(filename, "romfs:/zones/%u.zdf", this->id);

    FILE *zone_file = fopen(filename, "rb");
    if (!zone_file) {
        printf("Failed to locate zone %u\n", this->id);
        *left = *right = *top = *bottom = 0;
        return;
    }
    
    *left = this->loadU16(zone_file);
    *top = this->loadU16(zone_file);
    *right = this->loadU16(zone_file);
    *bottom = this->loadU16(zone_file);

    fclose(zone_file);
}

const std::vector<Entity*> &Zone::getComplexEntities() const {
    return this->complex_entities;
}

u16 Zone::getZoneId() const {
    return this->id;
}

void Zone::clear() {
    this->spritesheets.clear();
    for (Entity *entity : this->background_entities)
        delete entity;
    this->background_entities.clear();

    for (Entity *entity : this->more_background_entities)
        delete entity;
    this->more_background_entities.clear();

    for (Entity *entity : this->complex_entities)
        delete entity;
    this->complex_entities.clear();

    for (Entity *entity : this->foreground_entities)
        delete entity;
    this->foreground_entities.clear();

    for (Entity *entity : this->more_foreground_entities)
        delete entity;
    this->more_foreground_entities.clear();
}

void Zone::loadZonePart(std::vector<Entity*> *zone_part, FILE *zone_file) {
    for (u16 y = 0; y < ZONE_HEIGHT; y++) {
        for (u16 x = 0; x < ZONE_WIDTH; x++) {
            utils::SPRITESHEETS_ID spritesheet_id = (utils::SPRITESHEETS_ID)this->loadU16(zone_file);
            if (spritesheet_id) {
                if (spritesheet_id == 1)
                    break;

                u16 sprite_index = this->loadU16(zone_file);
                bool is_complex = false;
                entities::Entity *entity = this->createEntity(
                    spritesheet_id, sprite_index, 
                    x * TILE_SIZE, y * TILE_SIZE,
                    &is_complex
                );

                if (entity) {
                    if (is_complex)
                        this->complex_entities.push_back(entity);
                    else
                        zone_part->push_back(entity);
                }
            }
        }
    }
}

void Zone::loadZoneCollisions(FILE *zone_file) {
    u16 x = this->loadU16(zone_file);
    u16 y = this->loadU16(zone_file);
    u16 width = this->loadU16(zone_file);
    u16 height = this->loadU16(zone_file);
    u8 layer = fgetc(zone_file);
    while (x != 0 || y != 0 || width != 0 || height != 0) {
        this->complex_entities.push_back(new entities::Collision(
            (float)x, (float)y,
            (float)width, (float)height,
            layer
        ));

        x = this->loadU16(zone_file);
        y = this->loadU16(zone_file);
        width = this->loadU16(zone_file);
        height = this->loadU16(zone_file);
        layer = fgetc(zone_file);
    }
}

u16 Zone::loadU16(FILE *zone_file) {
    return fgetc(zone_file) | (fgetc(zone_file) << 8);
}

entities::Entity *Zone::createEntity(utils::SPRITESHEETS_ID spritesheet_id, u16 sprite_index, float x, float y, bool *is_complex) {
    switch (spritesheet_id) {
        case utils::SPRT_PLANT: case utils::SPRT_BLACK_FLAG: case utils::SPRT_BLUE_FLAG: case utils::SPRT_BROWN_FLAG:
        case utils::SPRT_GRAY_FLAG: case utils::SPRT_GREEN_FLAG: case utils::SPRT_RED_FLAG: case utils::SPRT_WHITE_FLAG:
        case utils::SPRT_YELLOW_FLAG:
            return new entities::AnimatedTile(x, y, TILE_SIZE, TILE_SIZE, spritesheet_id, 0, 3, 8);

        case utils::SPRT_DARK_MILL: case utils::SPRT_LIGHT_MILL:
            return new entities::AnimatedTile(x, y, TILE_SIZE * 4.f, TILE_SIZE * 4.f, spritesheet_id, 0, 3, 8);

        case utils::SPRT_GREEN_BAMBOO_BOTTOM:
            *is_complex = true;
            return new entities::Bamboo(x, y);
        
        case utils::SPRT_BLUE_SLIME_BOTTOM:
            *is_complex = true;
            return new entities::Slime(x, y);

        default:
            return new entities::Tile(x, y, TILE_SIZE, TILE_SIZE, spritesheet_id, sprite_index);
    }
}