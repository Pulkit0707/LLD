#include <bits/stdc++.h>
using namespace std;

class Engine{
    public:
    virtual void start()=0;
};

class Electric:public Engine{
    public:
    void start() override{
        cout<<"Starting electric engine"<<endl;
    }
};

class Petrol:public Engine{
    public:
    void start() override{
        cout<<"Starting Petrol engine"<<endl;
    }
};

class Car{
    protected:
    Engine *e;
    public:
    Car(Engine*e){
        this->e=e;
    }
    virtual void drive()=0;
};

class SUV:public Car{
    public:
    SUV(Engine*e):Car(e){}
    void drive() override{
        cout<<"driving suv"<<endl;
        e->start();
    }
};

class Sedan:public Car{
    public:
    Sedan(Engine*e):Car(e){}
    void drive() override{
        cout<<"driving sedan"<<endl;
        e->start();
    }
};

int main(){
    Engine*e1=new Electric();
    Engine*e2=new Petrol();
    Car*c1=new SUV(e1);
    Car*c2=new Sedan(e2);
    return 0;
}