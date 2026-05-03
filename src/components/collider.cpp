#include "components/collider.hpp"
#include <citro2d.h>
#include "entities/zone.hpp"
#include "utils/constants.hpp"
#include "utils/utilities.hpp"

using namespace components;

Collider::Collider(u8 visible, u8 scan, float x, float y, float width, float height) {
    this->visible = visible;
    this->scan = scan;

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Collider::~Collider() {
    // Do nothing
}

void Collider::render(entities::Entity *parent, float depth, entities::Zone *container) {
#ifdef LYNCHY_DEBUG
    C2D_DrawRectSolid(
        parent->getX() + this->x + container->getX(), parent->getY() + this->y + container->getY(),
        Z_INDEX_UI,
        this->width, this->height,
        DEBUG_COLLIDER_COLOR()
    );
#endif
}

void Collider::clampMovement(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container, float *dx, float *dy) {
    Collider *other_collider = other->getCollider();
    if (!other_collider || !(this->scan & other_collider->visible))
        return;

    float leftA =   this->x + parent->getX() + parent_container->getX();
    float rightA =  leftA + width;
    float topA =    this->y + parent->getY() + parent_container->getY();
    float bottomA = topA + height;

    float leftB =   other_collider->x + other->getX() + other_container->getX();
    float rightB =  leftB + other_collider->width;
    float topB =    other_collider->y + other->getY() + other_container->getY();
    float bottomB = topB + other_collider->height;

    bool overlapX = rightA > leftB && leftA < rightB;
    bool overlapY = bottomA > topB && topA < bottomB;

    if (overlapY && *dx != 0.0f) {
        float distance = (*dx > 0.0f)
            ? leftB - rightA
            : rightB - leftA;

        if ((*dx > 0.0f && distance >= 0.0f && distance < *dx) ||
            (*dx < 0.0f && distance <= 0.0f && distance > *dx)) {
            *dx = distance;
        }
    }

    if (overlapX && *dy != 0.0f) {
        float distance = (*dy > 0.0f)
            ? topB - bottomA
            : bottomB - topA;

        if ((*dy > 0.0f && distance >= 0.0f && distance < *dy) ||
            (*dy < 0.0f && distance <= 0.0f && distance > *dy)) {
            *dy = distance;
        }
    }
}

bool Collider::checkCollision(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container) {
    Collider *other_collider = other->getCollider();
    if (!other_collider)
        return false;
    
    if (!(this->scan & other_collider->visible))
        return false;
    
    float parent_x = this->x + parent->getX() + parent_container->getX();
    float parent_y = this->y + parent->getY() + parent_container->getY();
    float other_x = other_collider->x + other->getX() + other_container->getX();
    float other_y = other_collider->y + other->getY() + other_container->getY();

    return !(
        parent_x + this->width <= other_x ||
        parent_x >= other_x + other_collider->width ||

        parent_y + this->height <= other_y ||
        parent_y >= other_y + other_collider->height
    );
}

float Collider::getX() const {
    return this->x;
}

float Collider::getY() const {
    return this->y;
}

float Collider::getWidth() const {
    return this->width;
}

float Collider::getHeight() const {
    return this->height;
}

void Collider::setX(float x) {
    this->x = x;
}

void Collider::setY(float y) {
    this->y = y;
}

void Collider::setWidth(float width) {
    this->width = width;
}

void Collider::setHeight(float height) {
    this->height = height;
}

u8 Collider::getVisibleOn() const {
    return this->visible;
}