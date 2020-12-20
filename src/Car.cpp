#include "Car.h"

Car::Car() : Object(1, 20, 1, 20) {}
void Car::run()
{
    Object::run();
}