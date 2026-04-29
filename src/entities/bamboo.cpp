#include "systems/game.hpp"
using namespace entities;

Bamboo::Bamboo(float x, float y)
    : Entity(x, y) {
    this->addComponent(
        new components::AnimatedImage(SPRT_GREEN_BAMBOO_BOTTOM, 0, 0, 8, 1.f),
        COMP_IMAGE
    );

    this->addComponent(
        new components::Collider(
            COL_LAYER_ENEMY,
            COL_LAYER_TERRAIN | COL_LAYER_WATER,
            2.f, 11.f, 12.f, 5.f
        ),
        COMP_COLLIDER
    );

    this->addComponent(
        new components::Hitbox(COL_LAYER_PLAYER, 0.f, 0.f, TILE_SIZE, TILE_SIZE),
        COMP_HITBOX
    );

    this->addComponent(
        new components::Hurtbox(COL_LAYER_ENEMY, 0.f, 0.f, TILE_SIZE, TILE_SIZE),
        COMP_HURTBOX
    );

    this->addComponent(
        new components::SquaredDetector(100.f, TILE_SIZE),
        COMP_SQUARED_DETECTOR
    );
}

Bamboo::~Bamboo() {
    // Do nothing
}

void Bamboo::update(Zone *container) {
    Player *player = systems::GameSystem::getInstance().getPlayer();
    systems::ZoneSystem &zone_system = systems::ZoneSystem::getInstance();

    components::AnimatedImage *animated_image = static_cast<components::AnimatedImage*>(this->getComponent(COMP_IMAGE));
    animated_image->update(this, container);

    float dx = 0.f, dy = 0.f;
    components::SquaredDetector *detector = static_cast<components::SquaredDetector*>(this->getComponent(COMP_SQUARED_DETECTOR));
    detector->getMovement(this, container, player, zone_system.getActualZone(), &dx, &dy);

    this->moveXY(dx / ENEMY_BAMBOO_SP_RT, dy / ENEMY_BAMBOO_SP_RT);
    animated_image->animate(dx, dy, SPRT_GREEN_BAMBOO_LEFT, 0, 3, 1);
}

void Bamboo::render(float depth, Zone *container) {
    this->getComponent(COMP_IMAGE)->render(this, depth, container);

#ifdef LYNCHY_DEBUG
    this->getComponent(COMP_SQUARED_DETECTOR)->render(this, depth, container);
    this->getComponent(COMP_COLLIDER)->render(this, depth, container);
    this->getComponent(COMP_HURTBOX)->render(this, depth, container);
    this->getComponent(COMP_HITBOX)->render(this, depth, container);
#endif
}