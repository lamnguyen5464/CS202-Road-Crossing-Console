#include "Header.h"

// constructors
Object::Object(int x, int y, int z, int t) {
    curX = x;
    curY = y;
    move = z;
    delta = t;
    pixel = '\xDB';
    switch (curY)
    {
    case 20:
        body.push_back(Coord(0, 0));
        body.push_back(Coord(1, 0));
        body.push_back(Coord(0, 1));
        body.push_back(Coord(1, 1));
        body.push_back(Coord(2, 1));
        body.push_back(Coord(-1, 1));
        break;
    case 30:
        body.push_back(Coord(0, 0));
        body.push_back(Coord(1, 0));
        body.push_back(Coord(0, 1));
        body.push_back(Coord(1, 1));
        body.push_back(Coord(2, 1));
        body.push_back(Coord(-1, 1));
        break;
    default:
        break;
    }
}

// functions
void Object::draw(int x, int y){
    for(int i = 0; i < body.size(); i++){
        Game().addPixelToQueue(x + body[i].x, y + body[i].y, pixel);
    }
}

void Object::erase(int x, int y)
{
    for (int i = 0; i < body.size(); i++)
    {
        Game().addPixelToQueue(x + body[i].x, y + body[i].y, ' ');
    }
}

void Object::drawAll() 
{
    int i = 0;
    while (curX + i * delta < Game::getColumns() - 2 && curX + i * delta > 0)
    {
        if (Game().haveStopSignal()) return;
        draw(curX + i * delta, curY);
        ++i;
    }
}

void Object::eraseAll() 
{
    int i = 0;
    while (curX + i * delta < Game::getColumns() - 2 && curX + i * delta > 0)
    {
        if (Game().haveStopSignal()) return;
        erase(curX + i * delta, curY);
        ++i;
    }
}

void Object::updateCursor() 
{
    curX += move;
    if (move == 1 && curX == 1 + delta) curX = 1;
    else if (move == -1 && curX == Game::getColumns() - 3 + delta) curX = Game::getColumns() - 3;
}

void Object::updateDelta() {
    if (GlobalConfig::getInstance()->updated == false && (delta > 20 || delta < -20)) {
        GlobalConfig::getInstance()->updated = true;
        eraseAll();
        delta /= 2;
        if (move > 0) {
            curX = 1;
        }
        else { 
            curX = Game::getColumns() - 3;
        }
    }
}

void Object::run()
{
    while (1) {
        if (Game().haveStopSignal()) return;
        updateDelta();
        drawAll();
        Sleep(250);
        eraseAll();
        updateCursor();
    }
}

void Car::run()
{
    Object::run();
}

void Truck::run()
{
    Object::run();
}

Car::Car() : Object(1, 20, 1, Game::getColumns() - 1) {}
Truck::Truck() : Object(Game::getColumns() - 3, 30, -1, (Game::getColumns() - 1) * (-1)) {}


