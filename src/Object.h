#ifndef Object_h
#define Object_h

#include "Coord.h"
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

    virtual void run();
};





#endif
