#include "Header.h"

using namespace std;
GlobalConfig::GlobalConfig() {
    lastSignal = ' ';
}

GlobalConfig* GlobalConfig::instance = nullptr;

GlobalConfig* GlobalConfig::getInstance() {
    if (instance == nullptr) {
        instance = new GlobalConfig();
    }
    return instance;
}

