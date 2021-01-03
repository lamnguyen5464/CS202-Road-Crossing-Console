#include "Bird.hpp"

Bird::Bird() : Object(Game::getColumns() - 3, 10, -1, -20) {}
void Bird::run() {
    Object::run();
}