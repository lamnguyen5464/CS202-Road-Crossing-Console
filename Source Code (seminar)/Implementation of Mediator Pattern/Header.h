#include <iostream>
#include <vector>
using namespace std;

#ifndef header
#define header

class Object {
protected:
    Mediator* mediator;
    int num;
public: 
    Object() = default;
    void setMediator(Mediator* _mediator);
    void setNum(int n);
    virtual void setStatus() = 0;
    virtual void doAction() = 0;
};

class Patient : public Object {
private: 
    bool ready;
public: 
    Patient() {
        ready = false;
    }
    void doAction();
    void setStatus();
};

class Mediator
{
protected:
    vector<Object *> list;
public:
    Mediator() = default;
    virtual void notify(int n) = 0;
    void addObject(Object *o);
};

class Service : public Mediator {
public:
    Service() = default;
    Service(int n);
    void notify(int n);
};



#endif