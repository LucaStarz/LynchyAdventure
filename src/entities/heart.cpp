#include "entities/heart.hpp"
#include "utils/collisions.hpp"
#include "utils/sounds.hpp"
#include "systems/sfx.hpp"
#include "systems/game.hpp"
#include "systems/zone_system.hpp"

using namespace entities;

Heart::Heart(float x, float y) 
    : Entity(x, y, 9.f, 8.f) {
    this->image = new components::ImageComponent(utils::SPRT_HEART, 0);
    this->detector = new components::Collider(utils::COL_LAYER_NONE, utils::COL_LAYER_PLAYER, 0.f, 0.f, this->getWidth(), this->getHeight());
}

Heart::~Heart() {
    delete this->detector;
    delete this->image;
}

bool Heart::update(Zone *container) {
    entities::Player *player = systems::GameSystem::getInstance().getPlayer();
    entities::Zone *player_container = systems::ZoneSystem::getInstance().getActualZone();

    if (this->detector->checkCollision(this, container, player, player_container)
        || (player->getWeapon()->isEnable() && this->detector->checkCollision(this, container, player->getWeapon(), player_container))) {
        player->getLifeManager()->addLife(1);
        systems::SoundManager::getInstance().playSound(utils::SND_COIN);
        return false;
    }

    return true;
}

void Heart::render(float depth, Zone *container) {
    this->image->render(this, depth, container);

#ifdef LYNCHY_DEBUG
    this->detector->render(this, depth, container);
#endif
}