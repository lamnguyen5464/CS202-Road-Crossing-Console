
#include "Game.hpp"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void Game::goTo(int posX, int posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void Game::setWindowSize(int width, int height)
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    RECT r;
    GetWindowRect(consoleWindow, &r); //stores the console's current dimensions

    MoveWindow(consoleWindow, r.left, r.top, width, height, TRUE);
}

bool Game::controlDirectionKey(int &curX, int &curY, char signal){
    switch (signal){
        case 'W': curY--; return 1;
        case 'S': curY++; return 1;
        case 'A': curX--; return 1;
        case 'D': curX++; return 1;
    }
    return 0;
}

void Game::erasePixel(int x, int y){
    Game::goTo(x, y);
    cout<<' ';
}