#include "Dinosaur.h"

Dinosaur::Dinosaur() : Object(Game::getColumns() - 3, 10, -1, -20) {}
void Dinosaur::run() {
    Object::run();
}