#include "entities/player.hpp"
#include "utils/constants.hpp"
#include "utils/spritesheets.hpp"
#include "utils/collisions.hpp"
#include "systems/inputs.hpp"
#include "utils/directions.hpp"
#include "systems/game.hpp"
#include "systems/gfx.hpp"
#include "systems/save.hpp"
#include "systems/sfx.hpp"
#include "utils/sounds.hpp"

#define IDLE_ANIM   0
#define WALK_ANIM   1
#define ATTACK_ANIM 2
#define DEAD_ANIM   3

using namespace entities;

Player::Player() 
    : Entity(0.f, 0.f, TILE_SIZE, TILE_SIZE) {
    this->weapon = new Weapon(this->getX(), this->getY() + TILE_SIZE, TILE_SIZE, TILE_SIZE, 2, utils::COL_LAYER_ENEMY, utils::COL_LAYER_PLAYER, 0);
    this->coins = DEFAULT_PLAYER_COINS;

    this->animator = new components::Animator();
    this->addAnimations();

    this->life_manager = new components::LifeManager(0, 0, DEFAULT_PLAYER_INV_TIME);
    this->collider = new components::Collider(utils::COL_LAYER_PLAYER, utils::COL_LAYER_TERRAIN | utils::COL_LAYER_WATER, 2.f, 11.f, 12.f, 5.f);

    this->hurtbox = new components::Hurtbox(utils::COL_LAYER_PLAYER, 2.f, 3.f, 12.f, 13.f);
    this->movement = new components::Movement(DEFAULT_PLAYER_SPEED);
}

Player::~Player() {
    delete this->weapon;

    delete this->animator;
    delete this->life_manager;
    delete this->collider;
    delete this->hurtbox;
    delete this->movement;
}

bool Player::update(Zone *container) {
    systems::InputsSystem &inputs_system = systems::InputsSystem::getInstance();
    
    if (this->weapon->isEnable()) {
        this->animator->setCurrentAnimation(ATTACK_ANIM);
    } else {
        if (this->movement->getDx() == 0.f && this->movement->getDy() == 0.f)
            this->animator->setCurrentAnimation(IDLE_ANIM);
        else
            this->animator->setCurrentAnimation(WALK_ANIM);
        
        u8 direction = inputs_system.isKeyHeld(KEY_LEFT) ? utils::MOV_DIR_LEFT
            : inputs_system.isKeyHeld(KEY_RIGHT) ? utils::MOV_DIR_RIGHT : utils::MOV_DIR_NONE;
        direction |= inputs_system.isKeyHeld(KEY_UP) ? utils::MOV_DIR_TOP
            : inputs_system.isKeyHeld(KEY_DOWN) ? utils::MOV_DIR_BOTTOM : utils::MOV_DIR_NONE;

        this->movement->applyMovement(this, container, direction);
        this->checkPlayerOutOfScreen();
    }
    this->animator->update(this, container);

    this->weapon->update(container);
    this->weapon->checkParentInfo(this);
    if (inputs_system.isKeyDown(KEY_A))
        this->weapon->setEnable();
    else if (inputs_system.isKeyDown(KEY_SELECT))
        systems::SoundManager::getInstance().playSound(utils::SND_COIN);
    
    this->life_manager->update(this, container);
    return true;
}

void Player::render(float depth, Zone *container) {
    this->animator->render(this, depth, container);
    this->weapon->render(depth, container);

#ifdef LYNCHY_DEBUG
    this->collider->render(this, depth, container);
    this->hurtbox->render(this, depth, container);
#endif
}

components::Hurtbox *Player::getHurtbox() const {
    return this->hurtbox;
}

components::Collider *Player::getCollider() const {
    return this->collider;
}

components::LifeManager *Player::getLifeManager() const {
    return this->life_manager;
}

components::Movement *Player::getMovement() const {
    return this->movement;
}

components::Animator *Player::getAnimator() const {
    return this->animator;
}

void Player::checkPlayerOutOfScreen() {
    systems::GameSystem &game_system = systems::GameSystem::getInstance();
    float dx = this->movement->getDx();
    float dy = this->movement->getDy();
    
    if (this->getX() <= -8.f && dx < -MOVEMENT_DEADZONE) {
        game_system.changeState(systems::GameState::GS_TO_LEFT);
        this->weapon->setDisable();
    } else if (this->getX() >= SCREEN_WIDTH - 8.f && dx > MOVEMENT_DEADZONE) {
        game_system.changeState(systems::GameState::GS_TO_RIGHT);
        this->weapon->setDisable();
    } else if (this->getY() <= -8.f && dy < -MOVEMENT_DEADZONE) {
        game_system.changeState(systems::GameState::GS_TO_TOP);
        this->weapon->setDisable();
    }
    else if (this->getY() >= SCREEN_HEIGHT - 8.f && dy > MOVEMENT_DEADZONE) {
        game_system.changeState(systems::GameState::GS_TO_BOTTOM);
        this->weapon->setDisable();
    }
}

void Player::setLifeInfos(u8 life, u8 max_life) {
    this->life_manager->setActualLife(life);
    this->life_manager->setMaxLife(max_life);
}

void Player::getLifeInfos(u8 *life, u8 *max_life) {
    *life = this->life_manager->getActualLife();
    *max_life = this->life_manager->getMaxLife();
}

void Player::setCoins(u32 coins) {
    this->coins = coins;
}

void Player::addCoins(u32 coins) {
    if (this->coins + coins > MAX_COINS)
        this->coins = MAX_COINS;
    else
        this->coins += coins;
}

u32 Player::getCoins() const {
    return this->coins;
}

entities::Weapon *Player::getWeapon() const {
    return this->weapon;
}

void Player::setWeapon(utils::SPRITESHEETS_ID weapon_id) {
    utils::SPRITESHEETS_ID old_spritesheet = this->weapon->getSpritesheet();
    if (old_spritesheet != 0)
        systems::GraphicsSystem::getInstance().unloadSpritesheet(old_spritesheet);
    
    systems::SaveSystem::getInstance().loadWeaponData(this->weapon, weapon_id);
    systems::GraphicsSystem::getInstance().loadSpritesheet(weapon_id);
    this->weapon->updateDirection(this, this->animator);
}

utils::SPRITESHEETS_ID Player::getWeaponId() const {
    return this->weapon->getSpritesheet();
}

void Player::addAnimations() {
    u8 left = this->animator->addAnimation(utils::SPRT_PLAYER_LEFT, 0, 0, 0);
    u8 right = this->animator->addAnimation(utils::SPRT_PLAYER_RIGHT, 0, 0, 0);
    u8 top = this->animator->addAnimation(utils::SPRT_PLAYER_TOP, 0, 0, 0);
    u8 bottom = this->animator->addAnimation(utils::SPRT_PLAYER_BOTTOM, 0, 0, 0);
    this->animator->addOrientedAnimation(left, right, top, bottom);

    left = this->animator->addAnimation(utils::SPRT_PLAYER_LEFT, 1, 4, 8);
    right = this->animator->addAnimation(utils::SPRT_PLAYER_RIGHT, 1, 4, 8);
    top = this->animator->addAnimation(utils::SPRT_PLAYER_TOP, 1, 4, 8);
    bottom = this->animator->addAnimation(utils::SPRT_PLAYER_BOTTOM, 1, 4, 8);
    this->animator->addOrientedAnimation(left, right, top, bottom);

    left = this->animator->addAnimation(utils::SPRT_PLAYER_LEFT, 5, 5, 0);
    right = this->animator->addAnimation(utils::SPRT_PLAYER_RIGHT, 5, 5, 0);
    top = this->animator->addAnimation(utils::SPRT_PLAYER_TOP, 5, 5, 0);
    bottom = this->animator->addAnimation(utils::SPRT_PLAYER_BOTTOM, 5, 5, 0);
    this->animator->addOrientedAnimation(left, right, top, bottom);

    this->animator->addDeadAnimation();
}