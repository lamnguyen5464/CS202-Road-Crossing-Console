#include "Header.h"

using namespace std;


void testRun()
{
    int curX = 10, curY = 10;

    char pixel = '\xDB';
    vector<Coord> body;
    body.push_back(Coord(0, 0));
    body.push_back(Coord(1, 0));
    body.push_back(Coord(0, 1));
    body.push_back(Coord(1, 1));
    body.push_back(Coord(2, 1));
    body.push_back(Coord(-1, 1));
    Truck obj(pixel, body);

    obj.run();
}

void testPeople()
{
    int curX = 10, curY = 10;

    char pixel = '#';
    vector<Coord> body;
    body.push_back(Coord(0, 0));
    body.push_back(Coord(1, 1));
    body.push_back(Coord(-1, 1));
    body.push_back(Coord(0, 2));

    Car car(pixel, body);

    while (1)
    {
        if (Game().haveStopSignal()) return;
        int oldX = curX, oldY = curY;
        if (Game().controlDirectionKey(curX, curY, GlobalConfig::getInstance()->lastSignal)){
            car.erase(oldX, oldY);
            car.draw(curX, curY);
            GlobalConfig::getInstance()->lastSignal = ' ';
        }
    }
}


int main()
{
    Game().setWindowSize(Game().SCREEN_WIDTH, Game().SCREEN_HEIGHT);
    SetConsoleTitle("Game qua duong");

    cout << "Start test...." << endl;

    thread one(testRun);
    thread people(testPeople);
    thread keyboardListener(Game().eventKeyBoardListener);
    thread draw(Game().drawPixelInQueue);


    keyboardListener.join();
    draw.join();
    people.join();

    one.join();

    return 0;
};