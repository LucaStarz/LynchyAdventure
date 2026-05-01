#pragma once

#include <3ds.h>
#include <entities/zone.hpp>

namespace systems {
    class ZoneSystem final {
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