#ifndef Coord_h
#define Coord_h

class Coord {
public:
    int x; int y;
    Coord(int x, int y);
};

class Pixel : public Coord {
public:
    char pixel;
    Pixel(int x, int y, char pixel);
};

#endif