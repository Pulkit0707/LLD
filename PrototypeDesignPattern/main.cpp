#include <bits/stdc++.h>
using namespace std;

class Clonable{
    public:
    virtual Clonable* clone()=0;
};

class NPC:public Clonable{
    string name;
    int health,power;
    public:
    NPC(string name,int h,int p){
        name=name;
        health=h;
        power=p;
        cout<<"Setting template NPC"<<name<<endl;
    }
    NPC(NPC &npc){
        name=npc.name;
        health=npc.health;
        power=npc.power;
        cout<<"Cloning NPC"<<name<<endl;
    }
    Clonable*clone() override{
        return new NPC(*this);
    }
};

int main(){
    NPC*obj1=new NPC("N1",10,4);
    NPC*obj2=(NPC*)obj1->clone();
    return 0;
}