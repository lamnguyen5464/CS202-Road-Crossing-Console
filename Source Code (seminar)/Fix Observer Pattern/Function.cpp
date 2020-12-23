#include "Header.h"

void Subject::registerObserver (Observer* o) {
    list.push_back(o);
}

void Subject::unsubscribe (Observer* o) {
    for (int i = 0; i < list.size(); ++i) {
        if (o == list[i]) list.erase(list.begin() + i);
    }
}

void Subject::notify() {
    for (int i = 0; i < list.size(); ++i) {
        list[i]->update();
    }
}

int Match::getScoreTeam1() { return 0; }
int Match::getScoreTeam2() { return 1; }
string Match::getScorer() { return "Messi"; }

bool Match::scoreChanged() {return true; }

void Match::playing() {
    if (scoreChanged()) notify();
}

Normal::Normal(Match* s) {
    subject = s; 
    subject->registerObserver(this);
}
Pro::Pro(Match* s) { 
    subject = s; 
    subject->registerObserver(this);
}

void Pro::update() {
    s1 = subject->getScoreTeam1();
    s2 = subject->getScoreTeam2();
    name = subject->getScorer();
    display();
}

void Pro::display() {
    cout << "Updated score: " << s1 << " - " << s2 << ".\n"
    << "Scorer: " << name << endl;
}

void Normal::update() {
    s1 = subject->getScoreTeam1();
    s2 = subject->getScoreTeam2();
    display();
}

void Normal::display() {
    cout << "Updated score: " << s1 << " - " << s2 << endl;
}
