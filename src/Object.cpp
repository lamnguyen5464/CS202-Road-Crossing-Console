#include "Header.h"

// constructors
Object::Object(int x, int y, int z, int t)
{
    curX = x;
    curY = y;
    move = z;
    delta = t;
    pixel = '\xDB';
    switch (curY)
    {
    case 30:
        body.push_back(Coord(0, 0));
        // body.push_back(Coord(1, 0));
        // body.push_back(Coord(2, 0));
        // body.push_back(Coord(0, 1));
        // body.push_back(Coord(1, 1));
        // body.push_back(Coord(2, 1));
        // body.push_back(Coord(3, 1));
        // body.push_back(Coord(4, 1));
        // body.push_back(Coord(-1, 1));
        // body.push_back(Coord(-2, 1));
        break;
    case 25:
        body.push_back(Coord(0, 0));
        // body.push_back(Coord(0, 1));
        // body.push_back(Coord(1, 0));
        // body.push_back(Coord(1, 1));
        // body.push_back(Coord(2, 1));
        // body.push_back(Coord(-1, 1));
        // body.push_back(Coord(-1, 0));
        break;
    case 15:
        body.push_back(Coord(0, 3));
        // body.push_back(Coord(1, 2));
        // body.push_back(Coord(1, 3));
        // body.push_back(Coord(2, 1));
        // body.push_back(Coord(2, 2));
        // body.push_back(Coord(2, 3));
        // body.push_back(Coord(3, 1));
        // body.push_back(Coord(3, 2));
        // body.push_back(Coord(3, 3));
        // body.push_back(Coord(4, 0));
        // body.push_back(Coord(5, 0));
        break;
    case 10:
        body.push_back(Coord(1, -1));
        // body.push_back(Coord(2, -1));
        // body.push_back(Coord(0, 0));
        // body.push_back(Coord(-1, -1));
        // body.push_back(Coord(-2, -1));
        break;
    default:
        break;
    }
}

// functions
void Object::draw(int x, int y)
{
    for (int i = 0; i < body.size(); i++)
    {
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
        if (Game().haveStopSignal())
            return;
        draw(curX + i * delta, curY);
        ++i;
    }
}

void Object::eraseAll()
{
    int i = 0;
    while (curX + i * delta < Game::getColumns() - 2 && curX + i * delta > 0)
    {
        if (Game().haveStopSignal())
            return;
        erase(curX + i * delta, curY);
        ++i;
    }
}

void Object::updateCursor()
{
    curX += move;

    // if (move == 1 && curX == 3 + delta)
    //     curX = 3;
    // else if (move == -1 && curX == Game::getColumns() - 3 + delta)
    //     curX = Game::getColumns() - 3;
    if (type() == 2 || type() == 3) {
        if (curX == start + delta) curX = start;
        else if (curX == Game::getColumns() - 2) curX = 2;
    }
    else {
        if (curX == start + delta) curX = start;
        else if (curX == 1) curX = start;
    }
}

void Object::updateDelta()
{
    if (GlobalConfig::getInstance()->first == false && GlobalConfig::getInstance()->updated == false && (delta > 20 || delta < -20))
    {
        GlobalConfig::getInstance()->updated = true;
        eraseAll();
        delta /= 2;
        if (move > 0)
        {
            curX = 3;
        }
        else
        {
            curX = Game::getColumns() - 2;
        }
        switch (type())
        {
        case 1:
            GlobalConfig::getInstance()->d1 = delta;
            break;
        case 2:
            GlobalConfig::getInstance()->d2 = delta;
            break;
        case 3:
            GlobalConfig::getInstance()->d3 = delta;
            break;
        case 4:
            GlobalConfig::getInstance()->d4 = delta;
            break;
        default:
            break;
        }
    }
}

void Object::setDelta(int n)
{
    delta = n;
}

void Object::setStart(int n) {
    start = n;
}

void Object::run()
{
    while (1)
    {
        if (Game().haveStopSignal())
            return;
        if (GlobalConfig::getInstance()->light == '-' && (type() == 3 || type() == 4))
            continue;

        eraseAll();
        updateDelta();
        updateCursor();
        drawAll();
        switch (type())
        {
        case 1:
            Sleep(20);
            break;
        case 2:
            Sleep(200);
            break;
        case 3:
            Sleep(100);
            break;
        case 4:
            Sleep(150);
            break;
        default:
            break;
        }
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

void Dinasour::run()
{
    Object::run();
}

void Bird::run()
{
    Object::run();
}

int Bird::type() { return 1; }
int Dinasour::type() { return 2; }
int Car::type() { return 3; }
int Truck::type() { return 4; }

Bird::Bird() : Object(Game::getColumns() / 2, 10, -1, (Game::getColumns() - 1) * (-1))
{
    if (GlobalConfig::getInstance()->d1 != 0)
        setDelta(GlobalConfig::getInstance()->d1);
    setStart(Game::getColumns() - 2);
}

Dinasour::Dinasour() : Object(Game::getColumns() / 3, 15, 1, Game::getColumns() - 1)
{
    if (GlobalConfig::getInstance()->d2 != 0)
        setDelta(GlobalConfig::getInstance()->d2);
    setStart(2);
}

Car::Car() : Object(3, 25, 1, Game::getColumns() - 1)
{
    if (GlobalConfig::getInstance()->d3 != 0)
        setDelta(GlobalConfig::getInstance()->d3);
    setStart(2);
}

Truck::Truck() : Object(Game::getColumns() - 3, 30, -1, (Game::getColumns() - 1) * (-1))
{
    if (GlobalConfig::getInstance()->d4 != 0)
        setDelta(GlobalConfig::getInstance()->d4);
    setStart(Game::getColumns() - 2);
}