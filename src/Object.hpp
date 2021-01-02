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
    int curX, curY, delta, move;
public:
    Object() = default;
    Object(int x, int y, int z, int t);
    void draw(int x, int y);
    void erase(int x, int y);
    void drawAll();
    void eraseAll();
    void updateCursor();
    void updateDelta();

    virtual void run();
};
class Car : public Object
{
public: 
    Car();
    void run();

};

class Truck : public Object 
{
public:
    Truck();
    void run();
};




#endif