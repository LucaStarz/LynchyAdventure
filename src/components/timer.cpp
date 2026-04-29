#include "systems/game.hpp"

using namespace components;

Timer::Timer(u16 duration, bool repeat) {
    this->duration = duration;
    this->current = 0;
}

Timer::~Timer() {
    // Do nothing
}

void Timer::update(entities::Entity *parent, entities::Zone *container) {
    if (this->current < this->duration)
        this->current++;
    else if (this->repeat)
        this->current = 0;
}

bool Timer::isFinished() const {
    return this->current >= this->duration;
}

void Timer::reset() {
    this->current = 0;
}