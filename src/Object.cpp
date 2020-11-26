#include "Object.hpp"
#include "Game.hpp"
#include "Coord.hpp"
#include <vector>

using namespace std;


Object::Object(char pixel, vector<Coord> body){
    this->pixel = pixel;
    this->body = body;
}

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