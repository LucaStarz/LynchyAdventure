#include "systems/camera.hpp"
using namespace systems;

CameraSystem &CameraSystem::getInstance() {
    static CameraSystem instance;
    return instance;
}

CameraSystem::CameraSystem() {
    this->x = 0.f;
    this->y = 0.f;
    this->limit_x = 0.f;
    this->limit_y = 0.f;
}

CameraSystem::~CameraSystem() {
    // Do nothing
}

void CameraSystem::setLimitX(float x) {
    this->limit_x = x;
}

void CameraSystem::setLimitY(float y) {
    this->limit_y = y;
}

float CameraSystem::getX() const {
    return this->x;
}

float CameraSystem::getY() const {
    return this->y;
}

void CameraSystem::setX(float x) {
    this->x = x;
}

void CameraSystem::setY(float y) {
    this->y = y;
}