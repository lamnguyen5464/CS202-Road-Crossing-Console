#include "Header.h"


int main()
{
    Game().setWindowSize(Game().SCREEN_WIDTH, Game().SCREEN_HEIGHT);
    SetConsoleTitle("App game qua duong");

    int curX = 10, curY = 10;

    char pixel = '@';
    vector<Coord> body;
    // body.push_back(Coord(0,0));
    // body.push_back(Coord(-1, 1));
    // body.push_back(Coord(-2, 1));
    // body.push_back(Coord(1, 1));
    // body.push_back(Coord(2, 1));
    // body.push_back(Coord(0, 1));
    // body.push_back(Coord(0, 2));
    // body.push_back(Coord(1, 3));
    // body.push_back(Coord(-1, 3));

    body.push_back(Coord(0, 0));
    body.push_back(Coord(1, 0));
    body.push_back(Coord(0, 1));
    body.push_back(Coord(1, 1));
    body.push_back(Coord(2, 1));
    body.push_back(Coord(-1, 1));
    Car obj(pixel, body);
    // Car obj(pixel, body);                car di ve phai, truck di ve trai

    while (1)
    {
        char key = toupper(getch());
        if (key == 'Q')
            break;
        // obj.erase(curX, curY);
        // Game().controlDirectionKey(curX, curY, key);
        // obj.draw(curX, curY);
        obj.run();
    }
    return 0;
};