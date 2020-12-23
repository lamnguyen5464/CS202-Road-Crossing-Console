#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Observer {
public:
	virtual void update(string name, int score1, int score2) = 0;
};
class Subject {
public:
	virtual void registerObsever(Observer* o) = 0;
	virtual void unregisterObserver(Observer* o) = 0;
	virtual void notifyObserver() = 0;
};
class sportApp: public Subject{
private:
	int s1, s2;
	string n;
	vector<Observer*> obs;
public:
	sportApp() {}
	void registerObsever(Observer* o);
	void unregisterObserver(Observer* o);
	void notifyObserver();
	void editScore(string name, int score1, int score2);
	~sportApp(){}
};
class proScoreDisplay : public Observer {
private:
	int s1, s2;
	string n;
public:
	proScoreDisplay(){}
	void update(string name, int score1, int score2);
	void display();
	~proScoreDisplay(){}
};
class normalScoreDisplay : public Observer {
private:
	int s1, s2;
public:
	normalScoreDisplay(){}
	void update(string name, int score1, int score2);
	void display();
	~normalScoreDisplay(){}
};
#endif


