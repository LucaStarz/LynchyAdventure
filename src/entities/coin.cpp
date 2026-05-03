#include "entities/coin.hpp"
#include "entities/player.hpp"
#include "utils/spritesheets.hpp"
#include "systems/game.hpp"
#include "systems/zone_system.hpp"
#include "utils/collisions.hpp"
#include "utils/sounds.hpp"
#include "systems/sfx.hpp"

using namespace entities;

Coin::Coin(float x, float y)
    : Entity(x, y, 8.f, 8.f) {
    this->image = new components::AnimatedImage(utils::SPRT_COIN, 0, 3, 8);
    this->detector = new components::Collider(utils::COL_LAYER_NONE, utils::COL_LAYER_PLAYER, 0.f, 0.f, this->getWidth(), this->getHeight());
}

Coin::~Coin() {
    delete this->image;
    delete this->detector;
}

bool Coin::update(Zone *container) {
    this->image->update(this, container);
    entities::Player *player = systems::GameSystem::getInstance().getPlayer();
    entities::Zone *player_container = systems::ZoneSystem::getInstance().getActualZone();

    if (this->detector->checkCollision(this, container, player, player_container)
        || (player->getWeapon()->isEnable() && this->detector->checkCollision(this, container, player->getWeapon(), player_container))) {
        player->addCoins(1);
        systems::SoundManager::getInstance().playSound(utils::SND_COIN);
        return false;
    }

    return true;
}

void Coin::render(float depth, Zone *container) {
    this->image->render(this, depth, container);

#ifdef LYNCHY_DEBUG
    this->detector->render(this, depth, container);
#endif
}