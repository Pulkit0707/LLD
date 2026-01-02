#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Singleton{
    static Singleton* instance;
    static mutex mtx;
    Singleton(){
        cout<<"New singleton object";
    }
    public:
    static Singleton*getInstance(){
        if(instance==nullptr){
            lock_guard<mutex> lock(mtx);
            if(instance==nullptr){
                instance=new Singleton();
            }
        }
        return instance;
    }
};

Singleton* Singleton::instance=nullptr;

int main(){
    Singleton* s1=Singleton::getInstance();
    return 0;
}