#include <bits/stdc++.h>
using namespace std;

class Memento;

class Originator{
    protected:
    map<string,string>mp;
    public:
    void create(string key,string val){
        mp[key]=val;
    }
    void update(string key,string val){
        mp[key]=val;
    }
    void del(string key){
        mp.erase(key);
    }
    Memento*createMemento(){
        Memento*m=new Memento();
        m->setState(mp);
        return m;
    }
    void restore(Memento*m){
        map<string,string>m1=m->getState();
        mp=m1;
    }
    void display(){
        for(auto x:mp){
            cout<<x.first<<" "<<x.second<<endl;
        }
    }
};

class Memento{
    protected:
    map<string,string>mp;
    public:
    void setState(map<string,string>mp){
        this->mp=mp;
    }
    map<string,string> getState(){
        return this->mp;
    }
};

class Caretaker{
    protected:
    Memento* m;
    public:
    Caretaker(): m(nullptr){}
    ~Caretaker(){
        if(m) delete m;
    }
    void beginTxn(Originator*o){
        if(m) delete m;
        m=o->createMemento();
    }
    void commit(){
        if(m){
            delete m;
            m=nullptr;
        }
    }
    void rollback(Originator*o){
        o->restore(m);
        delete m;
        m=nullptr;
    }
};

int main(){
    Originator o;
    Caretaker c;
    c.beginTxn(&o);
    o.create("name","Alice");
    o.create("age","30");
    c.commit();
    o.display();
    c.beginTxn(&o);
    o.update("name","Bob");
    o.update("age","31");
    o.display();
    c.rollback(&o);
    o.display();
    return 0;
}