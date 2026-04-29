#include "systems/game.hpp"
using namespace systems;

ZoneSystem &ZoneSystem::getInstance() {
    static ZoneSystem instance;
    return instance;
}

ZoneSystem::ZoneSystem() {
    this->actual_zone = new entities::Zone(0.f, 0.f);
    this->left_zone = new entities::Zone(-SCREEN_WIDTH, 0.f);
    this->top_zone = new entities::Zone(0.f, -SCREEN_HEIGHT);
    this->right_zone = new entities::Zone(SCREEN_WIDTH, 0.f);
    this->bottom_zone = new entities::Zone(0.f, SCREEN_HEIGHT);
}

ZoneSystem::~ZoneSystem() {
    delete this->actual_zone;
    delete this->left_zone;
    delete this->right_zone;
    delete this->top_zone;
    delete this->bottom_zone;
}

void ZoneSystem::load(u16 zone_id) {
    u16 left, right, top, bottom;
    this->actual_zone->load(zone_id, &left, &right, &top, &bottom);

    this->left_zone->load(left, &left, &left, &left, &left);
    this->right_zone->load(right, &right, &right, &right, &right);
    this->top_zone->load(top, &top, &top, &top, &top);
    this->bottom_zone->load(bottom, &bottom, &bottom, &bottom, &bottom);
}

void ZoneSystem::update() {
    this->actual_zone->update(nullptr);
    this->left_zone->update(nullptr);
    this->right_zone->update(nullptr);
    this->top_zone->update(nullptr);
    this->bottom_zone->update(nullptr);
}

void ZoneSystem::renderBackground() {
    this->actual_zone->renderBackground();
    this->left_zone->renderBackground();
    this->right_zone->renderBackground();
    this->top_zone->renderBackground();
    this->bottom_zone->renderBackground();
}

void ZoneSystem::renderForeground() {
    this->actual_zone->renderForeground();
    this->left_zone->renderForeground();
    this->right_zone->renderForeground();
    this->top_zone->renderForeground();
    this->bottom_zone->renderForeground();
}

bool ZoneSystem::moveToLeft() {
    float movement_clamp = MIN(ZONE_MOVEMENT_X, -this->left_zone->getX());
    this->actual_zone->moveX(movement_clamp);
    this->left_zone->moveX(movement_clamp);
    GameSystem::getInstance().getPlayer()->moveX(movement_clamp);

    if (this->left_zone->getX() == 0.f) {
        entities::Zone *new_left = this->right_zone;
        new_left->setX(-SCREEN_WIDTH);

        this->right_zone = this->actual_zone;
        this->actual_zone = this->left_zone;
        this->left_zone = new_left;
        
        u16 left, right, top, bottom;
        this->actual_zone->getNeighbours(&left, &right, &top, &bottom);

        this->left_zone->load(left, &left, &left, &left, &left);
        this->top_zone->load(top, &top, &top, &top, &top);
        this->bottom_zone->load(bottom, &bottom, &bottom, &bottom, &bottom);
        return true;
    }

    return false;
}

bool ZoneSystem::moveToRight() {
    float movement_clamp = MIN(ZONE_MOVEMENT_X, this->right_zone->getX());
    this->actual_zone->moveX(-movement_clamp);
    this->right_zone->moveX(-movement_clamp);
    GameSystem::getInstance().getPlayer()->moveX(-movement_clamp);

    if (this->right_zone->getX() == 0.f) {
        entities::Zone *new_right = this->left_zone;
        new_right->setX(SCREEN_WIDTH);

        this->left_zone = this->actual_zone;
        this->actual_zone = this->right_zone;
        this->right_zone = new_right;
        
        u16 left, right, top, bottom;
        this->actual_zone->getNeighbours(&left, &right, &top, &bottom);

        this->right_zone->load(right, &right, &right, &right, &right);
        this->top_zone->load(top, &top, &top, &top, &top);
        this->bottom_zone->load(bottom, &bottom, &bottom, &bottom, &bottom);
        return true;
    }

    return false;
}

bool ZoneSystem::moveToBottom() {
    float movement_clamp = MIN(ZONE_MOVEMENT_Y, this->bottom_zone->getY());
    this->actual_zone->moveY(-movement_clamp);
    this->bottom_zone->moveY(-movement_clamp);
    GameSystem::getInstance().getPlayer()->moveY(-movement_clamp);

    if (this->bottom_zone->getY() == 0.f) {
        entities::Zone *new_bottom = this->top_zone;
        new_bottom->setY(SCREEN_HEIGHT);
        
        this->top_zone = this->actual_zone;
        this->actual_zone = this->bottom_zone;
        this->bottom_zone = new_bottom;

        u16 left, right, top, bottom;
        this->actual_zone->getNeighbours(&left, &right, &top, &bottom);

        this->left_zone->load(left, &left, &left, &left, &left);
        this->right_zone->load(right, &right, &right, &right, &right);
        this->bottom_zone->load(bottom, &bottom, &bottom, &bottom, &bottom);
        return true;
    }

    return false;
}

bool ZoneSystem::moveToTop() {
    float movement_clamp = MIN(ZONE_MOVEMENT_Y, -this->top_zone->getY());
    this->actual_zone->moveY(movement_clamp);
    this->top_zone->moveY(movement_clamp);
    GameSystem::getInstance().getPlayer()->moveY(movement_clamp);

    if (this->top_zone->getY() == 0.f) {
        entities::Zone *new_top = this->bottom_zone;
        new_top->setY(-SCREEN_HEIGHT);

        this->bottom_zone = this->actual_zone;
        this->actual_zone = this->top_zone;
        this->top_zone = new_top;

        u16 left, right, top, bottom;
        this->actual_zone->getNeighbours(&left, &right, &top, &bottom);

        this->left_zone->load(left, &left, &left, &left, &left);
        this->right_zone->load(right, &right, &right, &right, &right);
        this->top_zone->load(top, &top, &top, &top, &top);
        return true;
    }

    return false;
}

u16 ZoneSystem::getActualZoneId() const {
    return this->actual_zone->getZoneId();
}

const std::vector<entities::Entity*> &ZoneSystem::getComplexEntities() const {
    return this->actual_zone->getComplexEntities();
}

entities::Zone *ZoneSystem::getActualZone() const {
    return this->actual_zone;
}

entities::Zone *ZoneSystem::getLeftZone() const {
    return this->left_zone;
}

entities::Zone *ZoneSystem::getRightZone() const {
    return this->right_zone;
}

entities::Zone *ZoneSystem::getTopZone() const {
    return this->top_zone;
}

entities::Zone *ZoneSystem::getBottomZone() const {
    return this->bottom_zone;
}