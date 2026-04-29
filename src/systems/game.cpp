#include "systems/game.hpp"
using namespace systems;

GameSystem &GameSystem::getInstance() {
    static GameSystem instance;
    return instance;
}

GameSystem::GameSystem() {
    this->state = GameState::GS_IN_GAME;
    this->player = new entities::Player();
}

GameSystem::~GameSystem() {
    delete this->player;
}

void GameSystem::init() {
    SaveSystem &save_system = SaveSystem::getInstance();
    save_system.loadConfigurations();
    save_system.loadPlayerSave();
}

void GameSystem::update() {
    InputsSystem &inputs_system = InputsSystem::getInstance();
    ZoneSystem &zone_system = ZoneSystem::getInstance();
    
    inputs_system.update();
    if (inputs_system.isKeyDown(KEY_START))
        SaveSystem::getInstance().storePlayerSave();
    else if (inputs_system.isKeyDown(KEY_SELECT))
        this->player->takeDamage();

    switch (this->state) {
        case GameState::GS_IN_GAME:
            zone_system.update();
            this->player->update(nullptr);
            break;
        
        case GameState::GS_TO_LEFT:
            if (zone_system.moveToLeft())
                this->state = GameState::GS_IN_GAME;
            break;
        
        case GameState::GS_TO_RIGHT:
            if (zone_system.moveToRight())
                this->state = GameState::GS_IN_GAME;
            break;
        
        case GameState::GS_TO_TOP:
            if (zone_system.moveToTop())
                this->state = GameState::GS_IN_GAME;
            break;
        
        case GameState::GS_TO_BOTTOM:
            if (zone_system.moveToBottom())
                this->state = GameState::GS_IN_GAME;
            break;
        
        case GameState::GS_MAIN_MENU:
            PRINT("Main menu!\n");
            break;
        
        case GameState::GS_PAUSE_MENU:
            PRINT("Pause menu!\n");
            break;
        
        case GameState::GS_GAME_OVER:
            PRINT("Game over menu\n");
            break;
    }
}

void GameSystem::render() {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    GraphicsSystem &gfx_system = GraphicsSystem::getInstance();
    ZoneSystem &zone_system = ZoneSystem::getInstance();
    UISystem &ui_system = UISystem::getInstance();

    // Top screen
    gfx_system.drawTopScreen();
    zone_system.renderBackground();
    this->player->render(Z_INDEX_PLAYER, nullptr);
    zone_system.renderForeground();
    ui_system.renderTopScreenUI();

    // Bottom screen
#ifndef LYNCHY_DEBUG
    gfx_system.drawBottomScreen();
    ui_system.renderBottomScreenUI();
#endif

    C3D_FrameEnd(0);
}

void GameSystem::changeState(GameState direction_state) {
    this->state = direction_state;
    
    ZoneSystem &zone_system = ZoneSystem::getInstance();
    switch (this->state) {
        case GameState::GS_TO_LEFT:
            zone_system.getTopZone()->unload();
            zone_system.getBottomZone()->unload();
            zone_system.getRightZone()->unload();
            break;
        
        case GameState::GS_TO_RIGHT:
            zone_system.getTopZone()->unload();
            zone_system.getBottomZone()->unload();
            zone_system.getLeftZone()->unload();
            break;
        
        case GameState::GS_TO_BOTTOM:
            zone_system.getLeftZone()->unload();
            zone_system.getRightZone()->unload();
            zone_system.getTopZone()->unload();
            break;
        
        case GameState::GS_TO_TOP:
            zone_system.getLeftZone()->unload();
            zone_system.getRightZone()->unload();
            zone_system.getBottomZone()->unload();
            break;

        default: break;
    }
}

entities::Player *GameSystem::getPlayer() const {
    return this->player;
}