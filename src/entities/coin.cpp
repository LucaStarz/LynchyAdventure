#include "entities/coin.hpp"
#include "utils/spritesheets.hpp"
using namespace entities;

Coin::Coin(float x, float y)
    : Entity(x, y, 8.f, 8.f) {
    this->image = new components::AnimatedImage(utils::SPRT_COIN, 0, 3, 8);
}

Coin::~Coin() {
    delete this->image;
}

bool Coin::update(Zone *container) {
    this->image->update(this, container);
    return true;
}

void Coin::render(float depth, Zone *container) {
    this->image->render(this, depth, container);
}