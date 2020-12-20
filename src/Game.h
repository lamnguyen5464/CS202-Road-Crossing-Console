#include <thread>
#include "Object.h"
#include <vector>

#ifndef Game_h
#define Game_h


class Game
{
private:
public:
    static const int SCREEN_HEIGHT = 700;
    static const int SCREEN_WIDTH = 1000;

    static void clearConsole();
    static void goTo(int posX, int posY);
    static void setWindowSize(int width, int height);
    static bool controlDirectionKey(int& curX, int& curY, char signal);
    static bool haveStopSignal();
    static void addPixelToQueue(int x, int y, char pixel);
    static int getColumns();
    static int getRows();
    static void saveGame();
    static void loadGame();

    // screens:
    static void showMenu();
    static void showGroundPlay();

    //in other thread
    static void drawPixelInQueue();
    static void eventKeyBoardListener();
    static void notiListener();
};

#endif