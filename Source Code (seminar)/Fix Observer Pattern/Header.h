#include <iostream>
#include <vector>
using namespace std;

#ifndef header
#define header

class Subject;

class Observer {
public:
    Observer() = default;
    virtual void update() = 0;   
};

class Subject {
public:
    Subject() = default;
    void registerObserver (Observer* o);
    void unsubscribe(Observer* o);
    void notify();
private:
    vector <Observer*> list;
};

class Match : public Subject {
public: 
    Match() = default;
    int getScoreTeam1(); // method to get updated score 
    int getScoreTeam2(); // method to get updated score
    string getScorer();  // method to get scorer's name
    bool scoreChanged(); // if something happened
    void playing();
};

class Pro : public Observer {
private:
    int s1, s2;
    string name;
    Match* subject;
public: 
    Pro (Match* s);
    void display();
    void update();
};

class Normal : public Observer {
private:
    int s1, s2;
    Match* subject;
public:
    Normal (Match* s);
    void display();
    void update();
};



#endif