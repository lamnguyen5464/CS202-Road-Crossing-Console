#include "header.h"
void sportApp::registerObsever(Observer* o) {
	obs.push_back(o);
}
void sportApp::unregisterObserver(Observer* o) {
	for (int i = 0; i < obs.size(); ++i) {
		if (obs[i] == o) obs.erase(obs.begin() + i);
	}
}
void sportApp::notifyObserver() {
	for (int i = 0; i < obs.size(); ++i) {
		obs[i]->update(n,s1,s2);
	}
}
void sportApp::editScore(string name, int score1, int score2) {
	n = name;
	s1 = score1;
	s2 = score2;
	notifyObserver();
}
void proScoreDisplay::update(string name, int score1, int score2) {
	n = name;
	s1 = score1;
	s2 = score2;
}
void proScoreDisplay::display() {
	cout << "Pro account display: " << endl;
	cout << "The player who scores: " << n << endl;
	cout << "Score: " << s1 << " - " << s2 << endl;
}
void normalScoreDisplay::update(string name, int score1, int score2) {
	s1 = score1;
	s2 = score2;
}
void normalScoreDisplay::display() {
	cout << "Normal account display: " << endl;
	cout << "Score: " << s1 << " - " << s2 << endl;
}