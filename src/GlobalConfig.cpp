#include "Header.h"

using namespace std;
GlobalConfig::GlobalConfig()
{
    lastSignal = ' ';
}

GlobalConfig *GlobalConfig::instance = nullptr;

GlobalConfig *GlobalConfig::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GlobalConfig();
    }
    return instance;
}

void GlobalConfig::resetMatrix()
{
    drawing_matrix.clear();
    vector<char> tmp;
    for (int i = 0; i <= Game().getColumns(); i++)
    {
        tmp.push_back(' ');
    }

    for (int i = 0; i <= Game().getColumns(); i++)
    {
        drawing_matrix.push_back(tmp);
    }
}

void GlobalConfig::initNewData(int setScore)
{
    currentScore = setScore;
    if (first) first = false;
    else updated = false;
    People::getPeople()->curX = Game::getColumns() / 2;
    People::getPeople()->curY = Game::getRows() - 1;
}
