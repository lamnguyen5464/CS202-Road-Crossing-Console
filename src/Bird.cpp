#include "Bird.h"

Bird::Bird() : Object(1, 5, 1, 20) {}
void Bird::run() {
    Object::run();
}