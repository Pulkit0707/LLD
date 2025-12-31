#include <bits/stdc++.h>
using namespace std;

class Talkable{
    public:
    virtual void talk() = 0;
    virtual ~Talkable(){}
};

class NormalTalk: public Talkable{
    public:
    void talk() override{
        cout<<"Normal Talk"<<endl;
    }
};

class NotTalkable: public Talkable{
    public:
    void talk() override{
        cout<<"Not Talkable"<<endl;
    }
};

class Walkable{
    public:
    virtual void walk() = 0;
    virtual ~Walkable(){}
};

class NormalWalk: public Walkable{
    public:
    void walk() override{
        cout<<"Normal Walk"<<endl;
    }
};

class NotWalk: public Walkable{
    public:
    void walk() override{
        cout<<"Not Walkable"<<endl;
    }
};

class Flyable{
    public:
    virtual void fly() = 0;
    virtual ~Flyable(){}
};

class NormalFly: public Flyable{
    public:
    void fly() override{
        cout<<"Normal Fly"<<endl;
    }
};

class NotFly: public Flyable{
    public:
    void fly() override{
        cout<<"Not Flyable"<<endl;
    }
};

class Robot{
    Talkable* talkBehavior;
    Walkable* walkBehavior;
    Flyable* flyBehavior;
    public:
    Robot(Talkable*t,Walkable*w,Flyable*f){
        talkBehavior = t;
        walkBehavior = w;
        flyBehavior = f;
    }
    void walk(){
        walkBehavior->walk();
    }
    void talk(){
        talkBehavior->talk();
    }
    void fly(){
        flyBehavior->fly();
    }
    virtual void projection() = 0;
};

class CompanionRobot: public Robot{
    public:
    CompanionRobot(Talkable*t,Walkable*w,Flyable*f): Robot(t,w,f){}
    void projection() override{
        cout<<"Companion Robot Projection"<<endl;
    }
};

class WorkerRobot: public Robot{
    public:
    WorkerRobot(Talkable*t,Walkable*w,Flyable*f): Robot(t,w,f){}
    void projection() override{
        cout<<"Worker Robot Projection"<<endl;
    }
};

int main(){
    Robot*r1=new CompanionRobot(new NormalTalk(),new NormalWalk(),new NotFly());
    r1->projection();
    r1->talk();
    r1->walk();
    r1->fly();
    Robot*r2=new WorkerRobot(new NotTalkable(),new NormalWalk(),new NormalFly());
    r2->projection();
    r2->talk();
    r2->walk();
    r2->fly();
    return 0;
}