#include "entities/slime.hpp"
#include "utils/constants.hpp"
#include "utils/collisions.hpp"
#include "entities/coin.hpp"
#include "entities/heart.hpp"
#include "entities/player.hpp"
#include "systems/game.hpp"
#include "systems/zone_system.hpp"
#include <cstdlib>
#include "utils/utilities.hpp"

#define IDLE_WALK_ANIM  0
#define DEAD_ANIM       1

using namespace entities;

Slime::Slime(float x, float y)
    : Entity(x, y, TILE_SIZE, TILE_SIZE) {
    this->collider = new components::Collider(utils::COL_LAYER_ENEMY, utils::COL_LAYER_TERRAIN | utils::COL_LAYER_WATER, 2.f, 11.f, 12.f, 5.f);
    this->animator = new components::Animator();
    this->addAnimations();

    this->hitbox = new components::Hitbox(utils::COL_LAYER_PLAYER, 1, 0.f, 0.f, TILE_SIZE, TILE_SIZE);
    this->hurtbox = new components::Hurtbox(utils::COL_LAYER_ENEMY, 0.f, 0.f, TILE_SIZE, TILE_SIZE);
    this->dectector = new components::SquaredDetector(150.f);
    this->life_manager = new components::LifeManager(2, 2, ENEMY_SLIME_INV_TIME);
    this->movement = new components::Movement(ENEMY_SLIME_SPEED);
}

Slime::~Slime() {
    delete this->collider;
    delete this->animator;
    delete this->hitbox;
    delete this->hurtbox;
    delete this->dectector;
    delete this->life_manager;
    delete this->movement;
}

bool Slime::update(Zone *container) {
    this->life_manager->update(this, container);
    if (this->life_manager->isDead()) {
        this->animator->setCurrentAnimation(DEAD_ANIM);
        this->animator->update(this, container);
        if (this->animator->isAnimationFinished())
            return false;
    } else {
        Player *player = systems::GameSystem::getInstance().getPlayer();
        systems::ZoneSystem &zone_system = systems::ZoneSystem::getInstance();

        u8 direction = this->dectector->getDirectionTo(this, container, player, zone_system.getActualZone());
        this->movement->applyMovement(this, container, direction);
        this->animator->update(this, container);
        this->hitbox->checkHurtbox(this, container, player, zone_system.getActualZone());
    }

    return true;
}

void Slime::render(float depth, Zone *container) {
    this->animator->render(this, depth, container);

#ifdef LYNCHY_DEBUG
    this->dectector->render(this, depth, container);
    this->collider->render(this, depth, container);
    this->hurtbox->render(this, depth, container);
    this->hitbox->render(this, depth, container);
#endif
}

Entity *Slime::getLoot() const {
    u8 chance = rand() % 100;

    if (chance < 40)
        return new Coin(this->getX() + 4.f, this->getY() + 4.f);
    else if (chance < 80)
        return new Heart(this->getX() + 3.5f, this->getY() + 3.5f);
    
    return nullptr;
}

components::Hurtbox *Slime::getHurtbox() const {
    return this->hurtbox;
}

components::Collider *Slime::getCollider() const {
    return this->collider;
}

components::LifeManager *Slime::getLifeManager() const {
    return this->life_manager;
}

components::Movement *Slime::getMovement() const {
    return this->movement;
}

components::Animator *Slime::getAnimator() const {
    return this->animator;
}

void Slime::addAnimations() {
    u8 left = this->animator->addAnimation(utils::SPRT_BLUE_SLIME_LEFT, 0, 3, 8);
    u8 right = this->animator->addAnimation(utils::SPRT_BLUE_SLIME_RIGHT, 0, 3, 8);
    u8 top = this->animator->addAnimation(utils::SPRT_BLUE_SLIME_TOP, 0, 3, 8);
    u8 bottom = this->animator->addAnimation(utils::SPRT_BLUE_SLIME_BOTTOM, 0, 3, 8);
    this->animator->addOrientedAnimation(left, right, top, bottom);

    this->animator->addDeadAnimation();
    this->animator->setCurrentAnimation(IDLE_WALK_ANIM);
}