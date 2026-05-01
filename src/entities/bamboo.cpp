#include "entities/bamboo.hpp"
#include "utils/constants.hpp"
#include "utils/collisions.hpp"
#include "utils/spritesheets.hpp"
#include "systems/zone_system.hpp"
#include "entities/player.hpp"
#include "systems/game.hpp"

#define IDLE_ANIM   0
#define WALK_ANIM   1

using namespace entities;

Bamboo::Bamboo(float x, float y)
    : Entity(x, y, TILE_SIZE, TILE_SIZE) {
    this->collider = new components::Collider(utils::COL_LAYER_ENEMY, utils::COL_LAYER_TERRAIN | utils::COL_LAYER_WATER, 2.f, 11.f, 12.f, 5.f);
    this->animator = new components::Animator();
    this->addAnimations();
    
    this->hitbox = new components::Hitbox(utils::COL_LAYER_PLAYER, 1, 0.f, 0.f, TILE_SIZE, TILE_SIZE);
    this->hurtbox = new components::Hurtbox(utils::COL_LAYER_ENEMY, 0.f, 0.f, TILE_SIZE, TILE_SIZE);
    this->dectector = new components::SquaredDetector(100.f);
    this->life_manager = new components::LifeManager(1, 1, DEFAULT_PLAYER_INV_TIME);
    this->movement = new components::Movement(ENEMY_BAMBOO_SP_RT);
}

Bamboo::~Bamboo() {
    delete this->collider;
    delete this->animator;
    delete this->hitbox;
    delete this->hurtbox;
    delete this->dectector;
    delete this->life_manager;
    delete this->movement;
}

void Bamboo::update(Zone *container) {
    if (this->life_manager->isDead())
        return;

    Player *player = systems::GameSystem::getInstance().getPlayer();
    systems::ZoneSystem &zone_system = systems::ZoneSystem::getInstance();

    u8 direction = this->dectector->getDirectionTo(this, container, player, zone_system.getActualZone());
    this->movement->applyMovement(this, container, direction);
    this->animator->update(this, container);
    if (this->movement->getDx() == 0.f && this->movement->getDy() == 0.f)
        this->animator->setCurrentAnimation(IDLE_ANIM);
    else
        this->animator->setCurrentAnimation(WALK_ANIM);

    this->hitbox->checkHurtbox(this, container, player, zone_system.getActualZone());
}

void Bamboo::render(float depth, Zone *container) {
    if (this->life_manager->isDead())
        return;

    this->animator->render(this, depth, container);

#ifdef LYNCHY_DEBUG
    this->dectector->render(this, depth, container);
    this->collider->render(this, depth, container);
    this->hurtbox->render(this, depth, container);
    this->hitbox->render(this, depth, container);
#endif
}

components::Hurtbox *Bamboo::getHurtbox() const {
    return this->hurtbox;
}

components::Collider *Bamboo::getCollider() const {
    return this->collider;
}

components::LifeManager *Bamboo::getLifeManager() const {
    return this->life_manager;
}

components::Movement *Bamboo::getMovement() const {
    return this->movement;
}

components::Animator *Bamboo::getAnimator() const {
    return this->animator;
}

void Bamboo::addAnimations() {
    u8 left = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_LEFT, 0, 0, 0);
    u8 right = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_RIGHT, 0, 0, 0);
    u8 top = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_TOP, 0, 0, 0);
    u8 bottom = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_BOTTOM, 0, 0, 0);
    this->animator->addOrientedAnimation(left, right, top, bottom);

    left = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_LEFT, 0, 3, 8);
    right = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_RIGHT, 0, 3, 8);
    top = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_TOP, 0, 3, 8);
    bottom = this->animator->addAnimation(utils::SPRT_GREEN_BAMBOO_BOTTOM, 0, 3, 8);
    this->animator->addOrientedAnimation(left, right, top, bottom);
}