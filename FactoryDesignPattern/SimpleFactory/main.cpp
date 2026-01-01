#include <bits/stdc++.h>
using namespace std;

class Burger{
    public:
    virtual void prepare()=0;
    virtual ~Burger(){}
};

class Veg: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Veg Burger"<<endl;
    }
};

class Egg: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Egg Burger"<<endl;
    }
};

class NonVeg: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Non-Veg Burger"<<endl;
    }
};

class BurgerFactory{
    public:
    Burger* createBurger(string &type){
        if(type=="Veg"){
            return new Veg();
        }
        else if(type=="Egg"){
            return new Egg();
        }
        else if(type=="NonVeg"){
            return new NonVeg();
        }
        else{
            return nullptr;
        }
    }
};

int main(){
    BurgerFactory*factory=new BurgerFactory();
    string type="Egg";
    Burger*burger=factory->createBurger(type);
    burger->prepare();
    return 0; 
}