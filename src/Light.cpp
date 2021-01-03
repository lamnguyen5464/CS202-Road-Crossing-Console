#include "Light.hpp"

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void CLIGHT::lightSwitch() { red = !red; }

void CLIGHT::setCord(int coordX, int coordY)
{
	mX = coordX;
	mY = coordY;
	red = false;
}

void CLIGHT::draw()
{
	Game().goTo(mX, mY);
	if (red)
	{
		SetColor(4);
		cout << char(220);
		Game().goTo(mX, mY + 1);
		SetColor(8);
		cout << char(223);
	}
	else
	{
		SetColor(8);
		cout << char(220);
		Game().goTo(mX, mY + 1);
		SetColor(10);
		cout << char(223);
	}

	SetColor(15);
}
