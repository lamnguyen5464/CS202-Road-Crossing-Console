#include "Coord.h"
#include <vector>
using namespace std;

#ifndef people_h
#define people_h

class People
{
private:
    People();
    static People* ppl;

public:
    char pixel;
    vector<Coord> body;
    int curX, curY;
    void draw();
    void erase(int x, int y);
    static People* getPeople();
};

#endif
