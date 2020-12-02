#ifndef Coord_hpp
#define Coord_hpp

class Coord{
    public:
    int x; int y;
    Coord(int x, int y);
};

class Pixel: public Coord{
    public:
    char pixel;
    Pixel(int x, int y, char pixel);
};

#endif