#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Singleton{
    static Singleton* instance;
    Singleton(){
        cout<<"Singleton Instance Created"<<endl;
    }
    public:
    static Singleton*getInstance(){
        return instance;
    }
};

Singleton* Singleton::instance=new Singleton();

int main(){
    Singleton* s1=Singleton::getInstance();
    return 0;
}