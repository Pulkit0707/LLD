#include <bits/stdc++.h>
using namespace std;

class IMediator{
    public:
    virtual void sendAll(string from,string msg)=0;
    virtual void sendTo(string from,string to,string msg)=0;
    virtual void registerColleague(IColleague* colleague)=0;
};

class IColleague{
    protected:
    IMediator*mediator;
    public:
    string name;
    IColleague(IMediator*mediator){
        mediator=mediator;
        mediator->registerColleague(this);
    }
    virtual void sendAll(string msg)=0;
    virtual void sendTo(string to,string msg)=0;
    virtual void receive(string from,string msg)=0;
};

class ChatMediator:public IMediator{
    protected:
    vector<IColleague*>list;
    public:
    void sendAll(string from,string msg) override{
        for(auto c:list){
            if(c->name!=from){
                cout<<"sending "<<msg<<" to "<<c->name<<endl;
            }
        }
    }
    void sendTo(string from,string to,string msg) override{
        cout<<"sending "<<msg<<" to "<<to<<endl;
        for(auto c:list){
            if(c->name==to){
                c->receive(from,msg);
            }
        }
    }
    void registerColleague(IColleague*colleague) override{
        list.push_back(colleague);
    }
};

class User:public IColleague{
    public:
    User(IMediator*mediator,string name):IColleague(mediator){
        this->name=name;
    }
    void sendAll(string msg) override{
        mediator->sendAll(this->name,msg);
    }
    void sendTo(string to,string msg) override{
        mediator->sendTo(this->name,to,msg);
    }
    void receive(string from,string msg) override{
        cout<<"recieved "<<msg<<" from "<<from<<endl;
    }
};

int main(){
    IMediator*mediatore=new ChatMediator();
    IColleague*user1=new User(mediatore,"u1");
    IColleague*user2=new User(mediatore,"u2");
    IColleague*user3=new User(mediatore,"u3");
    mediatore->registerColleague(user1);
    mediatore->registerColleague(user2);
    mediatore->registerColleague(user3);
    user1->sendAll("hello everyone");
    user2->sendTo("u3","hello user3");
    return 0;
}