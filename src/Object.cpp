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
        // for (int i = 0; i < People::getPeople()->body.size(); ++i)
        // {
        //     if (p->pixel != ' ' && p->x == People::getPeople()->curX + People::getPeople()->body[i].x && p->y == People::getPeople()->curY + People::getPeople()->body[i].y)
        //         GlobalConfig::getInstance()->lastSignal = 'Q';
        // }
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
        draw(curX + i * delta, curY);
        ++i;
    }
}

void Object::eraseAll() 
{
    int i = 0;
    while (curX + i * delta < Game::getColumns() - 2 && curX + i * delta > 0)
    {
        erase(curX + i * delta, curY);
        ++i;
    }
}

void Object::updateCursor() 
{
    curX += move;
    if (move == 1 && curX == 21) curX = 1;
    else if (move == -1 && curX == Game::getColumns() - 23) curX = Game::getColumns() - 3;
}

void Object::run()
{
    while (1) {
        if (Game().haveStopSignal()) return;
        drawAll();
        Sleep(100);
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

Car::Car() : Object(1, 20, 1, 20) {}
Truck::Truck() : Object(Game::getColumns() - 3, 30, -1, -20) {}


