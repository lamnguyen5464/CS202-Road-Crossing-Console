#include "Header.h"


proScoreDisplay::proScoreDisplay() {
    s1 = 0;
    s2 = 0;
    name = "";
}

normalScoreDisplay::normalScoreDisplay() {
    s1 = 0;
    s2 = 0;
}

void normalScoreDisplay::update (int score1, int score2) {
    s1 = score1;
    s2 = score2;
    display();
}

void normalScoreDisplay::display() {
    cout << "Score: " << s1 << " - " << s2 << endl;
}

void proScoreDisplay::update(int score1, int score2, string name) {
    s1 = score1;
    s2 = score2;
    this->name = name;

    display();
}

void proScoreDisplay::display() {
    cout << "Score: " << s1 << " - " << s2 << endl;
    cout << "Scorer: " << name << endl;
}

// get score team 1 from stadium
int Match::getScoreTeam1() {
    return 3; // for example
}

// get score team 2 from stadium
int Match::getScoreTeam2() {
    return 2; // for example
}

// get name of scorer
string Match::getN() {
    string x;
    getline(cin, x);
    return x;
}

void Match::scoreChanged() {
    s1 = getScoreTeam1();
    s2 = getScoreTeam2();
    name = getN();

    p.update(s1, s2, name);
    n.update(s1, s2);
}