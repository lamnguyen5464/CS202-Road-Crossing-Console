#ifndef GlobalConfig_h
#define GlobalConfig_h

#include "Header.h"
#include <queue>

using namespace std;

class GlobalConfig {
private:
    GlobalConfig();
    static GlobalConfig* instance;
public:

    int currentScore = 0;
    int currentPeopleX, currentPeopleY;
    queue<Pixel*> drawingQueue;
    char lastSignal;
    vector< vector<char> > drawing_matrix;

    void resetMatrix();
    void initNewData();
    static GlobalConfig* getInstance();
    ~GlobalConfig();
};



#endif