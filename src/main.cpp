#include "Header.h"


int main()
{
    Game().setWindowSize(Game().SCREEN_WIDTH, Game().SCREEN_HEIGHT);
    SetConsoleTitle("Game qua duong");
    cout<<"Start test..."<<endl;
    Game().showMenu();

    Game().clearConsole();
    return 0;


};

