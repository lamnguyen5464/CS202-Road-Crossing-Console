#include "Header.h"

Object::Object(char pixel, vector<Coord> body, int x, int y, int z)
{
    this->pixel = pixel;
    this->body = body;
    move = x;
    curY = y;
    curX = z;
}

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

Car::Car(char pixel, vector<Coord> body) : Object(pixel, body, 2, 30, 1) {}
Truck::Truck(char pixel, vector<Coord> body) : Object(pixel, body, -2, 20, 120) {}

void Object::run()
{
    while (1)
    {
        if (Game().haveStopSignal())
            return;
        if (curX == 1)
        {
            int x = move;
            while (x <= 20)
            {
                for (int i = 0; i < 6; ++i)
                {
                    (*this).draw(curX + x + i * delta, curY);
                }
                Sleep(300);
                for (int i = 0; i < 6; ++i)
                {
                    (*this).erase(curX + x + i * delta, curY);
                }
                x += move;
            }
            x = 0;
        }
        else
        {
            int x = move;
            while (x >= -20)
            {
                for (int i = 0; i < 6; ++i)
                {
                    (*this).draw(curX + x - i * delta, curY);
                }
                Sleep(300);
                for (int i = 0; i < 6; ++i)
                {
                    (*this).erase(curX + x - i * delta, curY);
                }
                x += move;
            }
            x = 0;
        }
        // neu va cham gi do thi break
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