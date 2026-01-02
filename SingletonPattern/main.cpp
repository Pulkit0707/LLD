#include <bits/stdc++.h>
using namespace std;

class Singleton{
    static Singleton* instance;
    Singleton(){
        cout<<"New singleton object";
    }
    public:
    static Singleton*getInstance(){
        if(instance==nullptr){
            instance=new Singleton();
            return instance;
        }
        else{
            return instance;
        }
    }
};

Singleton* Singleton::instance=nullptr;

int main(){
    Singleton* s1=Singleton::getInstance();
    return 0;
}