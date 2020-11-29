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

    char pixel = '@';
    vector<Coord> body;
    body.push_back(Coord(0, 0));
    body.push_back(Coord(-1, 1));
    body.push_back(Coord(-2, 1));
    body.push_back(Coord(1, 1));
    body.push_back(Coord(2, 1));
    body.push_back(Coord(0, 1));
    body.push_back(Coord(0, 2));
    body.push_back(Coord(1, 3));
    body.push_back(Coord(-1, 3));

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
    SetConsoleTitle("App game qua duong");

    cout << "Start test...." << endl;

    thread one(testRun);
    thread sec(Game().eventKeyBoardListener);
    thread thi(testPeople);
    thread draw(Game().drawPixelInQueue);

    draw.join();

    one.join();
    sec.join();
    thi.join();
    cout << "End!" << endl;

    return 0;
};