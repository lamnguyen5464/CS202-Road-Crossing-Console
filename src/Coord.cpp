#include "Coord.hpp"

Coord::Coord(int x, int y){
    this->x = x;
    this->y = y;
}

Pixel::Pixel(int x, int y, char pixel):Coord(x,y){
    this->pixel = pixel;
}