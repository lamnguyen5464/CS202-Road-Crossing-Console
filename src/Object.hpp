#ifndef Object_hpp
#define Object_hpp

#include "Coord.hpp"
#include "Light.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Object
{
private:
    char pixel;
    vector<Coord> body;
    int curX, curY, delta, move;
    CLIGHT carLight, truckLight;
    int stoptime = 0;
public:
    Object() = default;
    Object(int x, int y, int z, int t);
    void draw(int x, int y);
    void erase(int x, int y);
    void drawAll();
    void eraseAll();
    void updateCursor();

    virtual void run();

    //Light
    void flipTruckLight();
    void flipCarLight();
};




#endif