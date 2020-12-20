#ifndef GlobalConfig_hpp
#define GlobalConfig_hpp

#include <queue>
#include "Coord.hpp"

using namespace std;

class GlobalConfig {
private:
    GlobalConfig();
    static GlobalConfig* instance;
public:
    queue<Pixel*> drawingQueue;
    bool** matrix;
    char lastSignal;
    static GlobalConfig* getInstance();
    ~GlobalConfig();
};



#endif