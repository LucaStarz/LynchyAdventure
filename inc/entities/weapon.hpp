#pragma once

#include "entities/entity.hpp"
#include "components/hitbox.hpp"
#include "components/image.hpp"

namespace entities {
    typedef struct {
        float offset_x, offset_y;
        float width, height;
    } WeaponDirection;

    class Weapon : public Entity {
    public:
        Weapon(float x, float y, float w, float h, u8 damage, u8 scan, u16 duration, u16 spritesheet, u16 sprite_index);
        ~Weapon();
    
        bool isEnable() const;
        void setEnable();
        void setDisable();

        void update(Zone *container) override;
        void render(float depth, Zone *container) override;

        void setSpritesheet(u16 spritesheet);
        void setDamage(u8 damage);
        void setDuration(u16 duration);
        void setDirectionInfo(u8 direction, float offset_x, float offset_y, float width, float height);
        void updateDirection(entities::Entity *parent, components::Animator *animator);

        u16 getSpritesheet() const;

        void checkParentInfo(entities::Entity *parent);
    private:
        bool enable;
        WeaponDirection directions[4];
        utils::FIXED_DIRECTION direction;

        components::Timer *timer;
        components::Hitbox *hitbox;
        components::ImageComponent *image;

        void checkHurtbox(Zone *container, Zone *other_container);
    };
}