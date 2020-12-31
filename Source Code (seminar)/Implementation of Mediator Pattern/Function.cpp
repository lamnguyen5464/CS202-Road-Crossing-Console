#include "Header.h"

// Object
void Object::setMediator(Mediator* _mediator) {
    this->mediator = _mediator;
}

void Object::setNum(int n) {
    num = n;
}

// Patient
void Patient::doAction() {
    cout << "Patient num. " << num << "has finished meeting doctor! \n";
    this->mediator->notify(num);
}

void Patient::setStatus() {
    ready = true;
    cout << "Patient number " << num << "is ready to meet doctor!\n"; 
    doAction();
}

// Mediator
void Mediator::addObject(Object *o)
{
    o->setMediator(this);
    o->setNum(list.size() + 1);
    list.push_back(o);
}

//Service
Service::Service(int n) {
    for (int i = 0; i < n; ++i) {
        Patient* p = new Patient;
        addObject(p);
    }
}

void Service::notify(int n)
{
    list[n]->setStatus();
}

