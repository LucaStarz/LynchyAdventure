#pragma once

#include "systems/inputs.hpp"

namespace systems {
    class ZoneSystem {
    public:
        static ZoneSystem &getInstance();

        ZoneSystem(const ZoneSystem&) = delete;
        ZoneSystem &operator=(const ZoneSystem&) = delete;

        void load(u16 zone_id);
        void update();

        void renderBackground();
        void renderForeground();

        bool moveToLeft();
        bool moveToRight();
        bool moveToBottom();
        bool moveToTop();

        u16 getActualZoneId() const;
        const std::vector<entities::Entity*> &getComplexEntities() const;

        entities::Zone *getActualZone() const;
        entities::Zone *getLeftZone() const;
        entities::Zone *getRightZone() const;
        entities::Zone *getTopZone() const;
        entities::Zone *getBottomZone() const;
    private:
        entities::Zone *left_zone, *right_zone, *top_zone, *bottom_zone;
        entities::Zone *actual_zone;
    
        ZoneSystem();
        ~ZoneSystem();
    };
}