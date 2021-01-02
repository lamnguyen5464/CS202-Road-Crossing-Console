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
        // if curY == 1 next stage
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

            char tmp = GlobalConfig::getInstance()->drawing_matrix[p->x][p->y];

            if (p->pixel != ' ' && tmp != ' ')
            {
                GlobalConfig::getInstance()->lastSignal = 'Q';
            }

            GlobalConfig::getInstance()->drawing_matrix[p->x][p->y] = p->pixel;

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

    //validate
    if (x < 0 || y < y || x > Game().getColumns() || y > Game().getRows())
    {
        return;
    }

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
    Truck obj;
    obj.run();
    if (Game().haveStopSignal())
        return;
}

void testCar()
{
    Car obj;
    obj.run();
    if (Game().haveStopSignal())
        return;
}

void testPeople()
{
    People::getPeople()->draw();
    while (1)
    {
        if (Game().haveStopSignal())
        {
            Game().saveGame();
            return;
        }
        int oldX = People::getPeople()->curX, oldY = People::getPeople()->curY;
        if (Game().controlDirectionKey(People::getPeople()->curX, People::getPeople()->curY, GlobalConfig::getInstance()->lastSignal))
        {
            People::getPeople()->erase(oldX, oldY);
            People::getPeople()->draw();

            GlobalConfig::getInstance()->lastSignal = ' ';
        }
    }
}

void Game::notiListener()
{
    // while (1)
    // {
    //     if (Game().haveStopSignal())
    //     {
    //         Game().clearConsole();
    //         Game().goTo(1, 1);
    //         cout << "you lose!!!" << endl;
    //         cout << "Press Q to exit";
    //         return;
    //     }
    // }
}

void Game::onNextLevel(){
    int currentColumn = Game().getColumns() - 5;
    int score = GlobalConfig::getInstance()->currentScore;

    string scoreStr = to_string(score);

    for(int i = 0; i < scoreStr.length(); i++){
        Game().addPixelToQueue(currentColumn + i, 2, ' ');
        Game().addPixelToQueue(currentColumn + i, 2, scoreStr[i]);
    }
}

void Game::showGroundPlay()
{
    GlobalConfig::getInstance()->resetMatrix();
    Game().clearConsole();
    Game().onNextLevel();
    Game().goTo(1, 40);

    cout << "@ Press Q to quit" << endl;

    std::thread keyboardListener(Game().eventKeyBoardListener);
    thread draw(Game().drawPixelInQueue);
    thread noti(Game().notiListener);
 
    thread testObj(testRun);
    // thread testOther(testCar);
    thread people(testPeople);

   people.join();
     Game().goTo(1,1);
    cout<<"herere";
    testObj.join();
    // testOther.join();
    

    draw.join();
    noti.join();

    Game().goTo(1,1);
    cout<<"You lose!"<<"Press Q to exit"<<endl;

    keyboardListener.join();

    GlobalConfig::getInstance()->lastSignal = ' ';
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
    const int numOfOptions = 3;
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
        Game().goTo(1, 3);
        cout << "Type \'W\' for up" << endl
             << " Type \'S\' for down";

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
        {
            Game().goTo((Game().getColumns() - options[i].length()) / 2, 10 + i * 2);
            cout << options[i];

            if (choice == i)
            {
                Game().goTo((Game().getColumns() - options[i].length()) / 2 - 4, 10 + i * 2);
                cout << ">>>";
            }
        }

        char getKey = toupper(getch());
        switch (getKey)
        {
        case 'W':
            choice = (!choice) ? numOfOptions - 1 : choice - 1;
            break;
        case 'S':
            choice = (choice + 1) % numOfOptions;
            break;
        case 13: //Enter
            switch (choice)
            {
            case 0:
                GlobalConfig::getInstance()->initNewData(0);
                Game().showGroundPlay();
                break;
            case 1:
                Game().loadGame();
                Game().showGroundPlay();
                break;
            case 2:
                return;
            }
            break;
        }
    }
}

void Game::saveGame()
{
    ofstream gameData;
    gameData.open("game_data.txt");
    gameData << GlobalConfig::getInstance()->currentScore << endl;
    gameData << People::getPeople()->curX << " " << People::getPeople()->curY << endl;
    gameData.close();
}

void Game::loadGame()
{
    ifstream gameData;
    gameData.open("game_data.txt");
    if (!gameData.is_open())
    {
        //set init config
        GlobalConfig::getInstance()->initNewData(0);
    }
    else
    {
        gameData >> GlobalConfig::getInstance()->currentScore;
        gameData >> People::getPeople()->curX >> People::getPeople()->curY;
        //add more data if need
        gameData.close();
    }
}
