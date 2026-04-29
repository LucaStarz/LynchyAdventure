#include "systems/game.hpp"
using namespace entities;

Player::Player() 
    : Entity(0.f, 0.f) {
    this->weapon = new Weapon(.0f, .0f, 2.f, 2.f, 2, COL_LAYER_ENEMY, DEFAULT_PLAYER_WEAPON_TIME, DEFAULT_PLAYER_WEAPON_SPR, 0);

    this->addComponent(
        new components::AnimatedImage(10, 0, 0, 8, 1.f),
        COMP_IMAGE
    );

    this->addComponent(
        new components::Collider(
            COL_LAYER_PLAYER,
            COL_LAYER_TERRAIN | COL_LAYER_WATER,
            2.f, 11.f, 12.f, 5.f
        ), COMP_COLLIDER
    );

    this->addComponent(
        new components::Hurtbox(
            COL_LAYER_PLAYER,
            2.f, 3.f, 12.f, 13.f
        ), COMP_HURTBOX
    );

    this->addComponent(
        new components::Movement(DEFAULT_PLAYER_SPEED),
        COMP_MOVEMENT
    );

    this->addComponent(
        new components::LifeManager(0, 0),
        COMP_LIFE
    );
}

Player::~Player() {
    delete this->weapon;
}

void Player::update(Zone *container) {
    components::AnimatedImage *animated_image = static_cast<components::AnimatedImage*>(this->getComponent(COMP_IMAGE));
    components::Movement *movement = static_cast<components::Movement*>(this->getComponent(COMP_MOVEMENT));

    systems::InputsSystem &inputs_system = systems::InputsSystem::getInstance();
    u8 direction = inputs_system.isKeyHeld(KEY_LEFT) ? MOV_DIR_LEFT
        : inputs_system.isKeyHeld(KEY_RIGHT) ? MOV_DIR_RIGHT : MOV_DIR_NONE;
    direction |= inputs_system.isKeyHeld(KEY_UP) ? MOV_DIR_TOP
        : inputs_system.isKeyHeld(KEY_DOWN) ? MOV_DIR_BOTTOM : MOV_DIR_NONE;
    
    float dx, dy;
    movement->applyMovement(this, container, direction, &dx, &dy);
    animated_image->update(this, container);
    animated_image->animate(dx, dy, SPRT_PLAYER_LEFT, 1, 4, 2);
    this->checkPlayerOutOfScreen(dx, dy);

    if (inputs_system.isKeyDown(KEY_A)) {
        this->weapon->setEnable();
    }
}

void Player::render(float depth, Zone *container) {
    this->getComponent(COMP_IMAGE)->render(this, depth, container);

#ifdef LYNCHY_DEBUG
    this->getComponent(COMP_COLLIDER)->render(this, depth, container);
    this->getComponent(COMP_HURTBOX)->render(this, depth, container);
#endif
}

void Player::checkPlayerOutOfScreen(float dx, float dy) {
    systems::GameSystem &game_system = systems::GameSystem::getInstance();
    if (this->getX() <= -8.f && dx < -MOVEMENT_DEADZONE)
        game_system.changeState(systems::GameState::GS_TO_LEFT);
    else if (this->getX() >= SCREEN_WIDTH - 8.f && dx > MOVEMENT_DEADZONE)
        game_system.changeState(systems::GameState::GS_TO_RIGHT);
    else if (this->getY() <= -8.f && dy < -MOVEMENT_DEADZONE)
        game_system.changeState(systems::GameState::GS_TO_TOP);
    else if (this->getY() >= SCREEN_HEIGHT - 8.f && dy > MOVEMENT_DEADZONE)
        game_system.changeState(systems::GameState::GS_TO_BOTTOM);
}

void Player::setLifeInfos(u8 life, u8 max_life) {
    components::LifeManager *life_manager = static_cast<components::LifeManager*>(this->getComponent(COMP_LIFE));
    life_manager->setActualLife(life);
    life_manager->setMaxLife(max_life);
}

void Player::getLifeInfos(u8 *life, u8 *max_life) {
    components::LifeManager *life_manager = static_cast<components::LifeManager*>(this->getComponent(COMP_LIFE));
    *life = life_manager->getActualLife();
    *max_life = life_manager->getMaxLife();
}

void Player::takeDamage() {
    components::LifeManager *life_manager = static_cast<components::LifeManager*>(this->getComponent(COMP_LIFE));
    life_manager->takeDamage(1);
}