#ifndef Object_hpp
#define Object_hpp

#include "Coord.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Object
{
private:
    char pixel;
    vector<Coord> body;

public:
    Object(char pixel, vector<Coord> body);
    void draw(int x, int y);
    void erase(int x, int y);
};

#endif