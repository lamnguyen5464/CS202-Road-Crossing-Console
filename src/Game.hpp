#ifndef Game_hpp
#define Game_hpp

class Game
{
public:
    static const int SCREEN_HEIGHT = 700;
    static const int SCREEN_WIDTH = 1000;

    static void goTo(int posX, int posY);
    static void setWindowSize(int width, int height);
    static bool controlDirectionKey(int &curX, int &curY, char signal);
    static void erasePixel(int x, int y);
};

#endif