#include <bits/stdc++.h>
using namespace std;

class INotification{
    public:
    virtual string getContent() = 0;
    virtual ~INotification() {}
};

class SimpleNotification: public INotification{
    public:
    string text;
    SimpleNotification(string text){
        this->text=text;
    }
    string getContent() override {
        cout << "This is a simple notification " << text << endl;
        return text;
    }
};

class INotificationDecorator: public INotification{
    protected:
    INotification*notification;
    public:
    INotificationDecorator(INotification*notification){
        this->notification=notification;
    }
    virtual ~INotificationDecorator(){
        delete notification;
    }
};

class TimeStampDecorator: public INotificationDecorator{
    public:
    TimeStampDecorator(INotification*notification): INotificationDecorator(notification){}
    string getContent() override{
        notification->getContent();
        cout<<"[TimeStamp: "<<time(0)<<"]"<<endl;
        return "";
    }
};

class SignatureDecorator: public INotificationDecorator{
    public:
    SignatureDecorator(INotification*notification): INotificationDecorator(notification){}
    string getContent() override{
        notification->getContent();
        cout<<"-- Sent from Notification System"<<endl;
        return "";
    }
};

class IObserver{
    public:
    virtual void update()=0;
    virtual ~IObserver(){}
};

class IObservable{
    public:
    virtual void add(IObserver*observer)=0;
    virtual void remove(IObserver*observer)=0;  
    virtual void notify()=0;
};

class NotificationObservable: public IObservable{
    private:
    INotification*notification;
    vector<IObserver*>observers;
    public:
    NotificationObservable(){
        notification=nullptr;
    }
    void add(IObserver*observer) override{
        observers.push_back(observer);
    }
    void remove(IObserver*observer) override{
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notify() override{
        for(auto observer: observers){
            observer->update();
        }
    }
    void setNotification(INotification*notification){
        if(this->notification!=nullptr){
            delete this->notification;
        }
        this->notification=notification;
        notify();
    }
    INotification* getNotification(){
        return notification;
    }
    string getNotificationContent(){
        return notification->getContent();
    }
    ~NotificationObservable(){
        if(notification!=nullptr){
            delete notification;
        }
    }
};

class Logger: public IObserver{
    private:
    NotificationObservable*no;
    public:
    Logger(NotificationObservable*no){
        this->no=no;
        no->add(this);
    }
    void update() override{
        cout<<"Logging Notification:"<<endl;
        no->getNotification();
    }
};

class NotificationEngine: public IObserver{
    private:
    NotificationObservable*no;
    vector<INotificationStrategy*>ns;
    public:
    NotificationEngine(NotificationObservable*no){
        this->no=no;
        no->add(this);
    }
    void addStrategy(INotificationStrategy*strategy){
        ns.push_back(strategy);
    }
    void update() override{
        for(auto strategy: ns){
            strategy->send(no->getNotification());
        }
    }
};

class INotificationStrategy{
    public:
    virtual void send(INotification*notification)=0;
    virtual ~INotificationStrategy(){}
};

class EmailStrategy: public INotificationStrategy{
    string email;
    public:
    EmailStrategy(string email){
        this->email=email;
    }
    void send(INotification*notification) override{
        cout<<"Sending Email Notification to "<<email<<":"<<endl;
        notification->getContent();
    }
};

class SMSStrategy: public INotificationStrategy{
    string phoneNumber;
    public:
    SMSStrategy(string phoneNumber){
        this->phoneNumber=phoneNumber;
    }
    void send(INotification*notification) override{
        cout<<"Sending SMS Notification to "<<phoneNumber<<":"<<endl;
        notification->getContent();
    }
};

class PopUpStartegy: public INotificationStrategy{
    public:
    void send(INotification*notification) override{
        cout<<"Showing Pop-Up Notification:"<<endl;
        notification->getContent();
    }
};

class NotificationService{
    private:
    vector<INotification*>notifications;
    NotificationObservable*observable;
    static NotificationService*instance;
    NotificationService(){
        observable=new NotificationObservable();
    }
    public:
    static NotificationService*getInstance(){
        if(!instance){
            instance=new NotificationService();
        }
        return instance;
    }
    NotificationObservable*getObservable(){
        return observable;
    }
    void sendNotification(INotification*notification){
        notifications.push_back(notification);
        observable->setNotification(notification);
    }
    ~NotificationService(){
        delete observable;
    }
};

NotificationService*NotificationService::instance=nullptr;


int main(){
    NotificationService*ns=NotificationService::getInstance();
    NotificationObservable*observable=ns->getObservable();
    Logger*logger=new Logger(observable);
    NotificationEngine*engine=new NotificationEngine(observable);
    engine->addStrategy(new EmailStrategy("user@example.com"));
    engine->addStrategy(new SMSStrategy("+1234567890"));
    engine->addStrategy(new PopUpStartegy());
    observable->add(logger);
    observable->add(engine);
    INotification*notification1=new SimpleNotification("Your order has been shipped.");
    notification1=new TimeStampDecorator(notification1);
    notification1=new SignatureDecorator(notification1);    
    ns->sendNotification(notification1);
    delete logger;
    delete engine;
    return 0;
}