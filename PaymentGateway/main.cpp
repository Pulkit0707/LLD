#include <bits/stdc++.h>
using namespace std;

class Bank{
    public: 
    virtual void validate()=0;
    virtual void transfer()=0;
    virtual void reportStatus()=0;
    virtual ~Bank() = default;
};

class BOB: public Bank{
    public:
    void validate() override{
        cout<<"Validating through BOB"<<endl;
    }
    void transfer() override{
        cout<<"Transferring through BOB"<<endl;
    }
    void reportStatus() override{
        cout<<"Reporting status through BOB"<<endl;
    }
};

class SBI: public Bank{
    public:
    void validate() override{
        cout<<"Validating through SBI"<<endl;
    }
    void transfer() override{
        cout<<"Transferring through SBI"<<endl;
    }
    void reportStatus() override{
        cout<<"Reporting status through SBI"<<endl;
    }
};

class BankFactory{
    public:
    static Bank* getBank(string bankName){
        if(bankName=="BOB"){
            return new BOB();
        }
        else if(bankName=="SBI"){
            return new SBI();
        }
        else{
            return nullptr;
        }
    }
};

class PaymentStrategy{
    public:
    virtual void pay()=0;
    virtual ~PaymentStrategy() = default;
};

class PaymentTemplate{
    Bank* bank;
    public:
    PaymentTemplate(Bank* bank): bank(bank){}
    void payment(){
        validate();
        transfer();
        reportStatus();
    }
    void validate(){
        bank->validate();
    }
    virtual void transfer() = 0;
    void reportStatus(){
        bank->reportStatus();
    }
};

class Paytm: public PaymentStrategy, public PaymentTemplate{
    public:
    Paytm(Bank* bank): PaymentTemplate(bank){}
    void pay() override{
        cout<<"Paying through Paytm"<<endl;
    }
    void transfer() override{
        cout<<"Transferring through Paytm"<<endl;
    }
};

class GooglePay: public PaymentStrategy, public PaymentTemplate{
    public:
    GooglePay(Bank* bank): PaymentTemplate(bank){}
    void pay() override{
        cout<<"Paying through Google Pay"<<endl;
    }
    void transfer() override{
        cout<<"Transferring through Google Pay"<<endl;
    }
};

class PaymentService{
    PaymentStrategy* strategy;
    PaymentRequest* request;
    public:
    PaymentService(PaymentStrategy* strategy, PaymentRequest* request): strategy(strategy), request(request){}
    void makePayment(){
        strategy->pay();
    }
};

class PaymentRequest{
    int amount;
    int from;
    int to;
    public:
    PaymentRequest(int amount, int from, int to): amount(amount), from(from), to(to){}
};

int main(){
    Bank* b1=BankFactory::getBank("BOB");
    Bank* b2=BankFactory::getBank("SBI");
    PaymentStrategy* p1=new Paytm(b1);
    PaymentStrategy* p2=new GooglePay(b2);
    PaymentRequest* request=new PaymentRequest(1000, 1, 2);
    PaymentService* service1=new PaymentService(p1, request);
    PaymentService* service2=new PaymentService(p2, request);
}