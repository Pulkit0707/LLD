#include <bits/stdc++.h>
using namespace std;

class PaymentRequest;

//====================== BANK ======================

class Bank{
public:
    virtual void validate() = 0;
    virtual void transfer() = 0;
    virtual void reportStatus() = 0;
    virtual ~Bank() = default;
};

class BOB : public Bank{
public:
    void validate() override{
        cout<<"Validating through BOB"<<endl;
    }

    void transfer() override{
        cout<<"Money transferred through BOB"<<endl;
    }

    void reportStatus() override{
        cout<<"BOB: Payment Successful"<<endl;
    }
};

class SBI : public Bank{
public:
    void validate() override{
        cout<<"Validating through SBI"<<endl;
    }

    void transfer() override{
        cout<<"Money transferred through SBI"<<endl;
    }

    void reportStatus() override{
        cout<<"SBI: Payment Successful"<<endl;
    }
};

//====================== FACTORY ======================

class BankFactory{
public:

    static Bank* getBank(string bankName){

        if(bankName=="BOB")
            return new BOB();

        if(bankName=="SBI")
            return new SBI();

        return nullptr;
    }
};

//====================== REQUEST ======================

class PaymentRequest{

public:

    int amount;
    int from;
    int to;

    PaymentRequest(int amount,int from,int to)
        : amount(amount),from(from),to(to){}
};

//====================== STRATEGY ======================

class PaymentStrategy{

public:

    virtual void pay(PaymentRequest* request)=0;

    virtual ~PaymentStrategy()=default;
};

//====================== TEMPLATE ======================

class PaymentTemplate{

protected:

    Bank* bank;

public:

    PaymentTemplate(Bank* bank):bank(bank){}

    // Template Method
    void payment(){

        bank->validate();

        transfer();

        bank->reportStatus();
    }

    virtual void transfer()=0;
};

//====================== PAYTM ======================

class Paytm : public PaymentStrategy, public PaymentTemplate{

public:

    Paytm(Bank* bank)
        : PaymentTemplate(bank){}

    void pay(PaymentRequest* request) override{

        cout<<"\n===== PAYTM ====="<<endl;

        cout<<"Amount : "<<request->amount<<endl;

        payment();
    }

    void transfer() override{

        cout<<"Paytm Processing Payment"<<endl;

        bank->transfer();
    }
};

//====================== GOOGLE PAY ======================

class GooglePay : public PaymentStrategy, public PaymentTemplate{

public:

    GooglePay(Bank* bank)
        : PaymentTemplate(bank){}

    void pay(PaymentRequest* request) override{

        cout<<"\n===== GOOGLE PAY ====="<<endl;

        cout<<"Amount : "<<request->amount<<endl;

        payment();
    }

    void transfer() override{

        cout<<"Google Pay Processing Payment"<<endl;

        bank->transfer();
    }
};

//====================== SERVICE ======================

class PaymentService{

    PaymentStrategy* strategy;

    PaymentRequest* request;

public:

    PaymentService(PaymentStrategy* strategy,
                   PaymentRequest* request)
        : strategy(strategy),
          request(request){}

    void makePayment(){

        strategy->pay(request);
    }
};

//====================== MAIN ======================

int main(){

    Bank* bob = BankFactory::getBank("BOB");
    Bank* sbi = BankFactory::getBank("SBI");

    PaymentStrategy* paytm = new Paytm(bob);
    PaymentStrategy* gpay = new GooglePay(sbi);

    PaymentRequest* request =
        new PaymentRequest(1000,1,2);

    PaymentService* service1 =
        new PaymentService(paytm,request);

    PaymentService* service2 =
        new PaymentService(gpay,request);

    service1->makePayment();

    service2->makePayment();
}