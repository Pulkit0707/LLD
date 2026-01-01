#include <bits/stdc++.h>
using namespace std;

class Burger{
    public:
    virtual void prepare()=0;
    virtual ~Burger(){}
};

class Pasta{
    public:
    virtual void prepare()=0;
    virtual ~Pasta(){}
};

class VegBurger: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Veg Burger"<<endl;
    }
};

class BasicVegBurger: public VegBurger{
    public:
    void prepare() override{
        cout<<"Preparing Basic Veg Burger"<<endl;
    }
};

class WheatVegBurger: public VegBurger{
    public:
    void prepare() override{
        cout<<"Preparing Wheat Veg Burger"<<endl;
    }
};

class ChickenBurger: public Burger{
    public:
    void prepare() override{
        cout<<"Preparing Chicken Burger"<<endl;
    }
};

class BasicChickenBurger: public ChickenBurger{
    public:
    void prepare() override{
        cout<<"Preparing Basic Chicken Burger"<<endl;
    }
};

class WheatChickenBurger: public ChickenBurger{
    public:
    void prepare() override{
        cout<<"Preparing Wheat Chicken Burger"<<endl;
    }
};

class VegPasta: public Pasta{
    public:
    void prepare() override{
        cout<<"Preparing Veg Pasta"<<endl;
    }
};

class VegWhiteSaucePasta: public VegPasta{
    public:
    void prepare() override{
        cout<<"Preparing Veg White Sauce Pasta"<<endl;
    }
};

class VegRedSaucePasta: public VegPasta{
    public:
    void prepare() override{
        cout<<"Preparing Veg Red Sauce Pasta"<<endl;
    }
};

class NonVegPasta: public Pasta{
    public:
    void prepare() override{
        cout<<"Preparing Non-Veg Pasta"<<endl;
    }
};

class NonVegWhiteSaucePasta: public NonVegPasta{
    public:
    void prepare() override{
        cout<<"Preparing Non-Veg White Sauce Pasta"<<endl;
    }
};

class NonVegRedSaucePasta: public NonVegPasta{
    public:
    void prepare() override{
        cout<<"Preparing Non-Veg Red Sauce Pasta"<<endl;
    }
};

class AbstractFactory{
    public:
    virtual Burger* createBurger(string &type)=0;
    virtual Pasta* createPasta(string &type)=0;
    virtual ~AbstractFactory(){}
};

class VegFactory: public AbstractFactory{
    public:
    Burger* createBurger(string &type) override{
        if(type=="Basic")
            return new BasicVegBurger();
        else if(type=="Wheat")
            return new WheatVegBurger();
        else
            return new VegBurger();
    }
    Pasta* createPasta(string &type) override{
        if(type=="White")
            return new VegWhiteSaucePasta();
        else if(type=="Red")
            return new VegRedSaucePasta();
        else
            return new VegPasta();
    }
};

class NonVegFactory: public AbstractFactory{
    public:
    Burger* createBurger(string &type) override{
        if(type=="Basic")
            return new BasicChickenBurger();
        else if(type=="Wheat")
            return new WheatChickenBurger();
        else
            return new ChickenBurger();
    }
    Pasta* createPasta(string &type) override{
        if(type=="White")
            return new NonVegWhiteSaucePasta();
        else if(type=="Red")
            return new NonVegRedSaucePasta();
        else
            return new NonVegPasta();
    }
};

int main(){
    string burgerType="Wheat";
    string pastaType="Red";
    AbstractFactory* vegFactory = new VegFactory();
    Burger*burger=vegFactory->createBurger(burgerType);
    Pasta*pasta=vegFactory->createPasta(pastaType);
    burger->prepare();
    pasta->prepare();
    return 0; 
}