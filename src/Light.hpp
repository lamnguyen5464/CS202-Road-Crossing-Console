#include "Game.hpp"
#include <Windows.h>

#ifndef Light_hpp
#define Light_hpp

class CLIGHT
{
private:
	int mX, mY;
	bool red;

public:
	CLIGHT() = default;

	void setCord(int coordX, int coordY);
	void lightSwitch();
	void draw();

	bool canGo() { return !red; }
};

#endif