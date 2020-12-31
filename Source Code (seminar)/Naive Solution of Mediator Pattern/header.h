#ifndef _HEADER_H_
#define _HEADER_H_
#include <iostream>
#include <vector>
using namespace std;

class Patient {
private:
	int No;
public:
	Patient() {}
	void setNum(int n);
	void startToMeetDoctor();
	void actionToOtherPatient();
	~Patient() {}
};

class HospitalService {
private:
	vector<Patient*> v;
public:
	HospitalService() {}
	HospitalService(int n);
	void notify(int i);
	void addPatient(Patient* p);
	~HospitalService() {}
};

#endif