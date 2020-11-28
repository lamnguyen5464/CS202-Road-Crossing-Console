#include <thread>
#include "Game.hpp"
#include "Coord.hpp"
#include "Object.hpp"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int flag = 0;

void funcThread1(){
    while (1){
        if (flag) return;
        cout<<"Type something...(type Q to return)"<<endl;
        Sleep(500);
    }
}

void funcThread2(){
    while (1){
        char t = toupper(getch());
        if (t=='Q'){
            flag = 1;
            return;
        }
        cout<<t<<endl;

    }
}

int main()
{
    cout<<"Start test...."<<endl;
    thread one(funcThread1);
    thread sec(funcThread2);

    cout<<"before join"<<endl;
    one.join();
    sec.join();
    cout<<"End!"<<endl;

    // Game().setWindowSize(Game().SCREEN_WIDTH, Game().SCREEN_HEIGHT);
    // SetConsoleTitle("App game qua duong");

    // int curX = 10, curY = 10;

    // char pixel = '@';
    // vector<Coord> body;
    // body.push_back(Coord(0,0));
    // body.push_back(Coord(-1, 1));
    // body.push_back(Coord(-2, 1));
    // body.push_back(Coord(1, 1));
    // body.push_back(Coord(2, 1));
    // body.push_back(Coord(0, 1));
    // body.push_back(Coord(0, 2));
    // body.push_back(Coord(1, 3));
    // body.push_back(Coord(-1, 3));

    // Object obj(pixel, body);


    // while (1)
    // {
    //     char key = toupper(getch());
    //     if (key == 'Q')
    //         break;
    //     obj.erase(curX, curY);
    //     Game().controlDirectionKey(curX, curY, key);
    //     obj.draw(curX, curY);

    // }
    return 0;
};