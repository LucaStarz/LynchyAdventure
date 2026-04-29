#include "systems/inputs.hpp"
using namespace systems;

InputsSystem &InputsSystem::getInstance() {
    static InputsSystem instance;
    return instance;
}

InputsSystem::InputsSystem() {
    this->held = 0;
    this->down = 0;
    this->up = 0;
}

InputsSystem::~InputsSystem() {
    // Do nothing
}

void InputsSystem::update() {
    hidScanInput();
    hidTouchRead(&this->mouse_position);

    this->held = hidKeysHeld();
    this->down = hidKeysDown();
    this->up = hidKeysUp();
}

bool InputsSystem::isKeyHeld(u32 key) const {
    return this->held & key;
}

bool InputsSystem::isKeyDown(u32 key) const {
    return this->down & key;
}

bool InputsSystem::isKeyUp(u32 key) const {
    return this->up & key;
}

touchPosition *InputsSystem::getTouchPosition() {
    return &this->mouse_position;
}