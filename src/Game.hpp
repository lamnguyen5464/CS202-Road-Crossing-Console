#include <thread>
#include "Object.hpp"
#include "tchar.h"
#include <vector>
#include "GlobalConfig.hpp"

#ifndef Game_hpp
#define Game_hpp

#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7
class Game{
private:
public:
    static const int SCREEN_HEIGHT = 700;
    static const int SCREEN_WIDTH = 1000;
    static const bool soundOn = true; 

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
    static void onNextLevel();

<<<<<<< HEAD
    //screens:
    void drawTitle(int height, int width);
    void drawRectangle(int, int, int, int);
    void removeRectangle(int, int, int, int);

=======
    static void showScore();
>>>>>>> main
    // screens:
    static void showMenu();
    static void showGroundPlay();
    static void showReplayMenu();

    //in other thread
    static void drawPixelInQueue();
    static void eventKeyBoardListener();

    
    //
    void fontsize(int, int);
    void textColor(int x);
    //
    //void soundSetting(bool &soundOn); 
    //void moveSound();
    //
};

#endif