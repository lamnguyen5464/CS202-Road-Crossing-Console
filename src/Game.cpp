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

    thread keyboardListener(Game().eventKeyBoardListener);
    thread draw(Game().drawPixelInQueue);
    thread noti(Game().notiListener);
 
    thread testObj(testRun);
    thread testOther(testCar);
    thread people(testPeople);

   people.join();
     Game().goTo(1,1);
    cout<<"herere";
    testObj.join();
    testOther.join();
    

    draw.join();
    noti.join();

    Game().goTo(1,1);
    cout<<"You lose!"<<"Press Q to exit"<<endl;

    keyboardListener.join();

    GlobalConfig::getInstance()->lastSignal = ' ';
}

void Game::showMenu()
{
    const int numOfOptions = 3;
    string options[numOfOptions] = {
        "New game",
        "Load game",
        "Exit",
    };
    string title = "----------MENU----------";
    int choice = 0;
    while (1)
    {
        Game().clearConsole();
        //instruction
        Game().goTo(1, 3);
        cout << "Type \'W\' for up" << endl
             << " Type \'S\' for down";

        //content
        Game().goTo((Game().getColumns() - title.length()) / 2, 1); //align center
        cout << title;

        for (int i = 0; i < 3; i++)
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
                GlobalConfig::getInstance()->first = true;
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
    gameData << GlobalConfig::getInstance()->d1 << " " << GlobalConfig::getInstance()->d2 << " " << GlobalConfig::getInstance()->d3 << " " << GlobalConfig::getInstance()->d4 << endl;
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
        gameData >> GlobalConfig::getInstance()->d1 >> GlobalConfig::getInstance()->d2 >> GlobalConfig::getInstance()->d3 >> GlobalConfig::getInstance()->d4;
        gameData.close();
    }
}
