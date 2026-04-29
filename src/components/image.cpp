#include "systems/game.hpp"
using namespace components;

ImageComponent::ImageComponent(u16 spritesheet_id, u16 index, float scale) {
    this->spritesheet_id = spritesheet_id;
    this->index = index;
    this->scale = scale;
}

ImageComponent::~ImageComponent() {
    // Do nothing
}

void ImageComponent::render(entities::Entity *parent, float depth, entities::Zone *container) {
    systems::GraphicsSystem &gfx_system = systems::GraphicsSystem::getInstance();
    C2D_DrawImageAt(
        gfx_system.getSprite(this->spritesheet_id, this->index),
        parent->getX() + container->getX(), parent->getY() + container->getY(),
        depth, nullptr,
        this->scale, this->scale
    );
}

void ImageComponent::setSpritesheetId(u16 spritesheet_id) {
    this->spritesheet_id = spritesheet_id;
}

void ImageComponent::setSpriteIndex(u16 index) {
    this->index = index;
}

void ImageComponent::setScale(float scale) {
    this->scale = scale;
}