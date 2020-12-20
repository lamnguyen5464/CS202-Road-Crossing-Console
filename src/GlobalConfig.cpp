#include "Header.h"

using namespace std;
GlobalConfig::GlobalConfig() {
    lastSignal = ' ';
    matrix = new bool* [Game::getRows()];
    for (int i = 0; i < Game::getRows(); ++i) {
        matrix[i] = new bool [Game::getColumns()] {0}; 
    }
}

GlobalConfig* GlobalConfig::instance = nullptr;

GlobalConfig* GlobalConfig::getInstance() {
    if (instance == nullptr) {
        instance = new GlobalConfig();
    }
    return instance;
}

