#include <bits/stdc++.h>
using namespace std;

class ModelTrainer{
    public:
    virtual void load(string path)=0;
    virtual void preProcess()=0;
    virtual void train()=0;
    virtual void evaluate()=0;
    virtual void save(string location)=0;
    const void templateMethod(const string&dataPath,const string&saveLocation){
        load(dataPath);
        preProcess();
        train();
        evaluate();
        save(saveLocation);
    }
};

class Model1:public ModelTrainer{
    public:
    void load(string path) override{
        cout<<"loading model1 "<<path<<endl;
    }
    void preProcess() override{
        cout<<"Preprocessing model1"<<endl;
    }
    void train() override{
        cout<<"training model1"<<endl;
    }
    void evaluate() override{
        cout<<"evaluating model1"<<endl;
    }
    void save(string location) override{
        cout<<"saving model1 "<<location<<endl;
    }
};

class Model2:public ModelTrainer{
    public:
    void load(string path) override{
        cout<<"loading model2 "<<path<<endl;
    }
    void preProcess() override{
        cout<<"Preprocessing model2"<<endl;
    }
    void train() override{
        cout<<"training model2"<<endl;
    }
    void evaluate() override{
        cout<<"evaluating model2"<<endl;
    }
    void save(string location) override{
        cout<<"saving model2 "<<location<<endl;
    }
};

int main(){
    ModelTrainer*m1=new Model1();
    m1->templateMethod("path1","save1");
    ModelTrainer*m2=new Model2();
    m2->templateMethod("path2","save2");
    return 0; 
}