#include "Dinosaur.hpp"

Dinosaur::Dinosaur() : Object(1, 15, 1, 20) {}
void Dinosaur::run() {
    Object::run();
}