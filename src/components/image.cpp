#include "components/image.hpp"
#include "systems/gfx.hpp"
#include "entities/zone.hpp"
#include "utils/utilities.hpp"

using namespace components;

ImageComponent::ImageComponent(u16 spritesheet_id, u16 sprite_index) {
    this->spritesheet_id = spritesheet_id;
    this->sprite_index = sprite_index;
}

ImageComponent::~ImageComponent() {
    // Do nothing
}

void ImageComponent::render(entities::Entity *parent, float depth, entities::Zone *container) {
    C2D_Image sprite = systems::GraphicsSystem::getInstance().getSprite(this->spritesheet_id, this->sprite_index);
    if (!sprite.subtex)
        return;

    C2D_DrawImageAt(
        sprite,
        parent->getX() + container->getX(), parent->getY() + container->getY(),
        depth, nullptr,
        parent->getWidth() / (float)sprite.subtex->width, parent->getHeight() / (float)sprite.subtex->height
    );
}

void ImageComponent::setSpritesheetId(u16 spritesheet_id) {
    this->spritesheet_id = spritesheet_id;
}

void ImageComponent::setSpriteIndex(u16 index) {
    this->sprite_index = index;
}

u16 ImageComponent::getSpritesheetId() const {
    return this->spritesheet_id;
}