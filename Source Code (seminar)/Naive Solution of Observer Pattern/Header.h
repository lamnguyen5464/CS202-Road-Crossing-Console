#include <iostream>
#include <string>
using namespace std;

#ifndef header
#define header

class Match {
private:
    int s1, s2;
    string name;
    proScoreDisplay p;
    normalScoreDisplay n;
public: 
    void scoreChanged();  // whenever the score is changed, this function is invoked.
    int getScoreTeam1();  // method to get current score of team 1
    int getScoreTeam2();  // method to get current score of team 2
    string getN();        // method to get name of scorer
};

class proScoreDisplay {
private:
    int s1, s2;
    string name;
public:
    // constructor 
    proScoreDisplay();

    void update(int score1, int score2, string name);
    void display();
};

class normalScoreDisplay {
private:
    int s1, s2;
public: 
    normalScoreDisplay();

    void update(int score1, int score2);
    void display();
};



#endif