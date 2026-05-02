#pragma once

#include "entities/entity.hpp"
#include <vector>
#include <cstdio>
#include "utils/spritesheets.hpp"

namespace entities {
    class Zone : public Entity {
    public:
        Zone(float x, float y);
        ~Zone();

        bool update(Zone *container) override;
        void renderBackground();
        void renderForeground();

        void load(u16 id, u16 *left, u16 *right, u16 *top, u16 *bottom);
        void unload();
        void getNeighbours(u16 *left, u16 *right, u16 *top, u16 *bottom);

        const std::vector<Entity*> &getComplexEntities() const;
        u16 getZoneId() const;
    private:
        std::vector<Entity*> background_entities;
        std::vector<Entity*> more_background_entities;
        std::vector<Entity*> foreground_entities;
        std::vector<Entity*> more_foreground_entities;

        std::vector<Entity*> complex_entities;

        std::vector<utils::SPRITESHEETS_ID> spritesheets;
        u16 id;

        void clear();
        void loadZonePart(std::vector<Entity*> *zone_part, FILE *zone_file);
        void loadZoneCollisions(FILE *zone_file);
        u16 loadU16(FILE *zone_file);
        entities::Entity *createEntity(utils::SPRITESHEETS_ID spritesheet_id, u16 sprite_index, float x, float y, bool *is_complex);
    };
}