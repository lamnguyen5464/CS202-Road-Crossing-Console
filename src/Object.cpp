#include "Header.h"

// constructors
Object::Object(char pixel, vector<Coord> body, int x, int y, int z, int t){
    this->pixel = pixel;
    this->body = body;
    move = x;
    curY = y;
    curX = z;
    delta = t;
}

Car::Car(char pixel, vector<Coord> body) : Object(pixel, body, 2, 30, 1, 20) {}
Truck::Truck(char pixel, vector<Coord> body) : Object(pixel, body, -2, 20, 128, -20) {}

// functions
void Object::draw(int x, int y){
    for(int i = 0; i < body.size(); i++){
        Game().goTo(x + body[i].x, y + body[i].y);
        cout<<pixel;
    }
}

void Object::erase(int x, int y){
    for(int i = 0; i < body.size(); i++){
        Game().goTo(x + body[i].x, y + body[i].y);
        cout<<' ';
    }
}

void Object::drawAll() 
{
    int i = 0;
    while (curX + i * delta < 130 && curX + i * delta > 0)
    {
        draw(curX + i * delta, curY);
        ++i;
    }
}

void Object::eraseAll() 
{
    int i = 0;
    while (curX + i * delta < 130 && curX + i * delta > 0)
    {
        erase(curX + i * delta, curY);
        ++i;
    }
}

void Object::updateCursor() 
{
    curX += move;
    if (move == 2 && curX == 21) curX = 1;
    else if (move == -2 && curX == 108) curX = 128;
}

void Object::run() 
{
    while (1) {
        drawAll();
        Sleep(20);
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