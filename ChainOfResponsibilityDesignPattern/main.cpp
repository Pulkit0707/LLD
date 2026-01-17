#include <bits/stdc++.h>
using namespace std;

class MoneyHandler{
    protected:
    MoneyHandler* next;
    public:
    MoneyHandler(){
        this->next=nullptr;
    }
    void setHandler(MoneyHandler*mh){
        next=mh;
    }
    virtual void dispense(int amt)=0;
};

class ThousandHandler:public MoneyHandler{
    int numNotes;
    public:
    ThousandHandler(int notes){
        numNotes=notes;
    }
    void dispense(int amt) override{
        int notesNeeded=amt/1000;
        if(notesNeeded<=numNotes){
            numNotes-=notesNeeded;
            cout<<"Handled by 1000 handler and returned"<<endl;
        }
        else{
            cout<<"Handled partially by 1000 handler"<<endl;
            numNotes=0;
            if(next!=nullptr)
            next->dispense(amt-numNotes*1000);
            else
            cout<<"Sufficient amt not available"<<endl;
        }
    }
};

class FiveHundredHandler:public MoneyHandler{
    int numNotes;
    public:
    FiveHundredHandler(int notes){
        numNotes=notes;
    }
    void dispense(int amt) override{
        int notesNeeded=amt/500;
        if(notesNeeded<=numNotes){
            numNotes-=notesNeeded;
            cout<<"Handled by 500 handler and returned"<<endl;
        }
        else{
            cout<<"Handled partially by 500 handler"<<endl;
            numNotes=0;
            if(next!=nullptr)
            next->dispense(amt-numNotes*500);
            else
            cout<<"Sufficient amt not available"<<endl;
        }
    }
};

class HundredHandler:public MoneyHandler{
    int numNotes;
    public:
    HundredHandler(int notes){
        numNotes=notes;
    }
    void dispense(int amt) override{
        int notesNeeded=amt/100;
        if(notesNeeded<=numNotes){
            numNotes-=notesNeeded;
            cout<<"Handled by 100 handler and returned"<<endl;
        }
        else{
            if(next!=nullptr)
            next->dispense(amt-numNotes*100);
            else
            cout<<"Sufficient amt not available"<<endl;
        }
    }
};

int main(){
    MoneyHandler*thousandH=new ThousandHandler(5);
    MoneyHandler*fiveHundredH=new FiveHundredHandler(3);
    MoneyHandler*hundredH=new HundredHandler(6);
    thousandH->setHandler(fiveHundredH);
    fiveHundredH->setHandler(hundredH);
    thousandH->dispense(550000);
    return 0;
}