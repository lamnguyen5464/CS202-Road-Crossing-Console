#include "header.h"

void Patient::startToMeetDoctor() {
	cout << "Patient " << No << " start to meet doctor " << endl;
	this->actionToOtherPatient();
}
void Patient::actionToOtherPatient() {
	cout << "Patient " << No << " has already met doctor " << endl;
}
void Patient::setNum(int n) {
	No = n;
}

HospitalService::HospitalService(int n) {
	Patient* p = nullptr;
	for (int i = 0; i < n; ++i) {
		p = new Patient;
		p->setNum(i + 1);
		v.push_back(p);
	}
}
void HospitalService::notify(int i) {
	for (int i = 0; i < v.size(); ++i) {
		v[i]->startToMeetDoctor();
	}
}
void HospitalService::addPatient(Patient* p) {
	p->setNum(v.size() + 1);
	v.push_back(p);
}