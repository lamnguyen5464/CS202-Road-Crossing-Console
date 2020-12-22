#include "Header.h"

void Game::clearConsole()
{
    system("CLS");
}

int Game::getRows()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return rows;
}

int Game::getColumns()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

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

bool Game::controlDirectionKey(int &curX, int &curY, char signal)
{
    switch (signal)
    {
    case 'W':
        curY--;
        return 1;
    case 'S':
        curY++;
        return 1;
    case 'A':
        curX--;
        return 1;
    case 'D':
        curX++;
        return 1;
    }
    return 0;
}

bool Game::haveStopSignal()
{
    return GlobalConfig::getInstance()->lastSignal == 'Q';
}

void Game::drawPixelInQueue()
{
    while (1)
    {
        while (GlobalConfig::getInstance()->drawingQueue.size() != 0)
        {
            Pixel *p = GlobalConfig::getInstance()->drawingQueue.front();
            GlobalConfig::getInstance()->drawingQueue.pop();
            Game().goTo(p->x, p->y);
            cout << p->pixel;
        }
        if (Game().haveStopSignal())
            return;
    }
}

void Game::addPixelToQueue(int x, int y, char pixel)
{
    Pixel *p = new Pixel(x, y, pixel);
    GlobalConfig::getInstance()->drawingQueue.push(p);
}

void Game::eventKeyBoardListener()
{
    while (1)
    {
        char t = toupper(getch());
        GlobalConfig::getInstance()->lastSignal = t;
        if (Game().haveStopSignal())
            return;
    }
}

void testRun()
{
    int curX = 10, curY = 10;

    char pixel = '\xDB';
    vector<Coord> body;
    body.push_back(Coord(0, 0));
    body.push_back(Coord(1, 0));
    body.push_back(Coord(0, 1));
    body.push_back(Coord(1, 1));
    body.push_back(Coord(2, 1));
    body.push_back(Coord(-1, 1));
    Truck obj(pixel, body);

    obj.run();
}

void testPeople()
{
    int curX = 10, curY = 10;

    char pixel = '#';
    vector<Coord> body;
    body.push_back(Coord(0, 0));
    body.push_back(Coord(1, 1));
    body.push_back(Coord(-1, 1));
    body.push_back(Coord(0, 2));

    Car car(pixel, body);

    while (1)
    {
        if (Game().haveStopSignal())
            return;
        int oldX = curX, oldY = curY;
        if (Game().controlDirectionKey(curX, curY, GlobalConfig::getInstance()->lastSignal))
        {
            car.erase(oldX, oldY);
            car.draw(curX, curY);
            GlobalConfig::getInstance()->lastSignal = ' ';
        }
    }
}

void Game::showGroundPlay()
{
    Game().clearConsole();
    Game().goTo(1, 40);
    cout << "@ Press Q to quit" << endl;

    std::thread keyboardListener(Game().eventKeyBoardListener);
    thread draw(Game().drawPixelInQueue);

    thread testObj(testRun);
    thread people(testPeople);

    keyboardListener.join();
    draw.join();

    people.join();
    testObj.join();
}

void Game::fontsize(int x, int y){
    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();  
  lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);  
  GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx);  
  lpConsoleCurrentFontEx->dwFontSize.X = x;  
  lpConsoleCurrentFontEx->dwFontSize.Y = y;  
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx); 
}

void Game::textColor(int x){
   HANDLE cout_handle=GetStdHandle(STD_OUTPUT_HANDLE);
   cout_handle=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(cout_handle, x);
}

void Game::drawTitle(int height, int width) {
    
    const signed char TITLE[][82] = { { 32,95,95,95,95,95,32,32,        32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,'_',32,	   32,32,32,32,32,  32,32,32,'_','_','_','_',32,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		   },
						                { (char) 178,32,32,'_','_',32,92,32,	 32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,(char) 178,32,(char) 178,	   32,32,32,32,32,  32,32,'/',32,'_','_','_',(char) 178,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,'_',32,	  32,32,32,32,32,32,32,		   },
						                { (char) 178,32,(char) 178,'_','_',')',32,')', 32,32,'_','_','_',32,32,	 32,32,'_','_',32,'_',32,	  32,32,'_','_',(char) 178,32,(char) 178,	   32,32,32,32,32,  32,'/',32,32,(char) 178,32,32,32,		32,'_',32,'_','_',32,	 32,32,'_','_','_',32,32,	 32,'_','_','_',32,    32,'_','_','_',32,	 '(','_',')', 32,'_',32,'_','_',32,32,	  32,32,'_','_',32,'_',32},
							            { (char) 178,32,32,'_',32,32,'/',32,	 32,'/',32,'_',32,'\\',32,	 32,'/',32,'_','\'',32,(char) 178,	  32,'/',32,'_',32,32,(char) 178,	   32,32,32,32,32,  (char) 124,'|',32,32,(char) 178,32,32,32,		(char) 178,32,'\'','_','_',(char) 178, 32,'/',32,'_',32,'\\',32,	 '/',32,'_','_',(char) 178,   '/',32,'_','_',(char) 178,   (char) 178,32,(char) 178,  '|',32,'\'','_',32,'\\',32, 32,'/',32,'_','\'',32,(char) 178},
							            { (char) 178,32,(char) 178,32,92,32,92,32,	 '(',32,'(','_',')',32,')',	 '(',32,'(','_',')',32,(char) 178,	  '(',32,'(','_',')',32,(char) 178,   32,32,32,32,32,  32,'\\',32,32,(char) 178,'_','_','_',  (char) 178,32,(char) 178,32,32,32,	 '(',32,'(','_',')',32,')',  '\\','_','_',32,'\\', '\\','_','_',32,'\\', (char) 178,32,(char) 178,  '|',32,(char) 178,32,'|',32,'|',	  '(',32,'(','_',')',32,(char) 178},
							            { (char) 178,'_',(char) 178,32,32,92,'_',92,	 32,'\\','_','_','_','/',32, 32,'\\','_','_',',','_',(char) 178, 32,'\\','_','_',',','_',(char) 178, 32,32,32,32,32,  32,32,'\\','_','_','_','_',(char) 178, (char) 178,'_',(char) 178,32,32,32,	 32,'\\','_','_','_','/',32, (char) 178,'_','_','_','/',  (char) 178,'_','_','_','/',  (char) 178,'_',(char) 178, '|','_',(char) 178,32,'|','_','|', 32,'\\','_','_',',',32,(char) 178},
							            { 32,32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,32,32,		   32,32,32,32,32,  32,32,32,32,32,32,32,32,		32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		  32,(char) 178,'_','_','_','/'} };

    //(char)168->(char)124
    int row = (getRows()- height) / 2-10;
	int col = (getColumns() - width) / 2;
	int i, j;
	for (i = 0; i < height; ++i) {
		goTo(col, row++);
		for (j = 0; j < width; ++j) {
			Game().textColor(ColorCode_Yellow);
			cout << TITLE[i][j];
		}
	}
	Game().textColor(default_ColorCode);
}

void Game::drawRectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
   --topLeftX;
	--topLeftY;
	++bottomRightX;
	++bottomRightY; 
	
	int i;

    Game().goTo(topLeftX, topLeftY);
	cout << char(218);
	for (i = topLeftX + 1; i < bottomRightX; ++i)
		cout << char(196);
	cout << char(191);

	for (i = topLeftY + 1; i < bottomRightY; ++i) {
		Game().goTo(topLeftX, i);
		cout << char(179);
		Game().goTo(bottomRightX, i);
		cout << char(179);
	}

	Game().goTo(topLeftX, bottomRightY);
	cout << char(192);
	for (i = topLeftX + 1; i < bottomRightX; ++i)
		cout << char(196);
	cout << char(217);
}

void Game::removeRectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
    --topLeftX;
	--topLeftY;
	++bottomRightX;
	++bottomRightY;

	int i;

    Game().goTo(topLeftX, topLeftY);
	cout << " ";
	for (i = topLeftX + 1; i < bottomRightX; ++i)
		cout << " ";
	cout << " ";

	for (i = topLeftY + 1; i < bottomRightY; ++i) {
		Game().goTo(topLeftX, i);
		cout << " ";
		Game().goTo(bottomRightX, i);
		cout << " ";
	}

	Game().goTo(topLeftX, bottomRightY);
	cout << " ";
	for (i = topLeftX + 1; i < bottomRightX; ++i)
		cout << " ";
	cout << " ";
}

void Game::showMenu()
{
    int numOfOptions = 3;
    string options[numOfOptions] = {
        "New game",
        "Load game",
        "Exit",
    };
    string title = "---------MENU---------";
    string name="ROSSING ROAD";
    int choice = 0;
    while (1)
    {
        Game().clearConsole();
        //instruction
        Game().goTo(1, 30);
        cout<<"Type \'W\' for up"<<endl<<" Type \'S\' for down";
        Game().drawRectangle(1, 29, 18,32);

        //content
        Game().goTo((Game().getColumns() - title.length()) / 2, 18); //allign center
        Game().textColor(ColorCode_Yellow);
        cout << title;
        Game().textColor(ColorCode_DarkBlue);
        Game().goTo(Game().getColumns()/2, 2);

        Game().drawTitle(7, 82);
        Game().textColor(default_ColorCode);

    Game().drawRectangle(getColumns()/2-10, getRows()/4+8, getColumns()/2+10,getRows()/4+15);

        for (int i = 0; i < 3; i++)
        {   
            Game().goTo((Game().getColumns() - options[i].length()) / 2, 20 + i*2);
            Game().textColor(ColorCode_DarkGreen);
            cout<<options[i];

            if (choice == i){
                Game().goTo((Game().getColumns() - options[i].length()) / 2 - 4, 20 + i*2);
                Game().textColor(ColorCode_Grey);
                cout<<">>>";
            }
        }

        char getKey = toupper(getch());
        switch (getKey){
            case 'W':
            choice = (!choice) ? numOfOptions - 1 : choice - 1;
            break;
            case 'S':
            choice = (choice + 1) % numOfOptions;
            break;
            case 13: //Enter
            switch(choice){
                case 0: Game().showGroundPlay(); break;
                case 1: break;
                case 2: return;
            }
            break;
        }
    }
}
