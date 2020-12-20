#include "Truck.h"

Truck::Truck() : Object(Game::getColumns() - 3, 30, -1, -20) {}
void Truck::run()
{
    Object::run();
}