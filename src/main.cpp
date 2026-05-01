#include "systems/game.hpp"
#include <cstdlib>

int main(int argc, char **argv) {
    srand(time(nullptr));
    systems::GameSystem &game_system = systems::GameSystem::getInstance();
    
    game_system.init();
    while (aptMainLoop()) {
        game_system.update();
        game_system.render();
    }

    return 0;
}