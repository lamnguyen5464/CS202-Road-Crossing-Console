#ifndef GlobalConfig_hpp
#define GlobalConfig_hpp

#include "Header.h"
#include <queue>

using namespace std;

class GlobalConfig{
    private:
    GlobalConfig();
    static GlobalConfig* instance;
    public:

    int currentScore = 0;
    bool first = true;
    int currentPeopleX, currentPeopleY;
    bool updated = true;
    queue<Pixel*> drawingQueue;
    char lastSignal;
    vector< vector<char> > drawing_matrix;

    void resetMatrix();
    void initNewData(int setScore);
    static GlobalConfig* getInstance();
    ~GlobalConfig();
};



#endif