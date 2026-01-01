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

class NonVeg: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Non-Veg Burger"<<endl;
    }
};

class VegWheat: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Veg Wheat Burger"<<endl;
    }
};

class NonVegWheat: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Non-Veg Wheat Burger"<<endl;
    }
};

class BurgerFactory{
    public:
    virtual Burger*createBurger(string& type)=0;
};

class NormalBurgerFactory: public BurgerFactory{
    public:
    Burger*createBurger(string& type) override{
        if(type=="Veg"){
            return new Veg();
        }
        else if(type=="NonVeg"){
            return new NonVeg();
        }
        else{
            return nullptr;
        }
    }
};

class WheatBurgerFactory: public BurgerFactory{
    public:
    Burger*createBurger(string &type) override{
        if(type=="Veg"){
            return new VegWheat();
        }
        else if(type=="NonVeg"){
            return new NonVegWheat();
        }
        else{
            return nullptr;
        }
    }
};

int main(){
    string type="NonVeg";
    BurgerFactory*factory=new WheatBurgerFactory();
    Burger*burger=factory->createBurger(type);
    burger->prepare();
    return 0; 
}