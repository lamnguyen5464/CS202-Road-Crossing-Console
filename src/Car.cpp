#include "Car.hpp"

Car::Car() : Object(Game::getColumns() - 3, 25, -1, -20) {}
void Car::run()
{
    Object::run();
}