#include "Header.h"
#define SetConsoleTitle
// rows: 41 (0 - 40)
// colums: 134 (0 - 133)
int main() 
{
    Game().setWindowSize(Game().SCREEN_WIDTH, Game().SCREEN_HEIGHT);
    SetConsoleTitle("Game qua duong");
    cout<<"Start test..."<<endl;
    Game().showMenu();

    Game().clearConsole();

    return 0;
};

