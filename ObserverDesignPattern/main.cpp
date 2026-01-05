#include <bits/stdc++.h>
using namespace std;

class ISubscriber{
    public:
    virtual void update()=0;
    virtual ~ISubscriber(){}
};

class IChannel{
    public:
    virtual void subscribe(ISubscriber* subscriber)=0;
    virtual void unsubscribe(ISubscriber* subscriber)=0;
    virtual void notify()=0;
    virtual ~IChannel(){}
};

class Channel: public IChannel{
    public:
    string name,lastVideo;
    vector<ISubscriber*> subscribers;
    Channel(string channelName){
        name=channelName;
    }
    void subscribe(ISubscriber* subscriber) override{
        subscribers.push_back(subscriber);
    }
    void unsubscribe(ISubscriber* subscriber) override{
        subscribers.erase(remove(subscribers.begin(),subscribers.end(),subscriber),subscribers.end());
    }
    void notify() override{
        for(auto subscriber: subscribers){
            subscriber->update();
        }
    }
    void uploadVideo(string videoTitle){
        lastVideo=videoTitle;
        cout<<"Channel: "<<name<<" uploaded a new video: "<<lastVideo<<endl;
        notify();
    }
    string getLastVideo(){
        return lastVideo;
    }
};

class Subscriber: public ISubscriber{
    public:
    string name;
    Channel* channel;
    Subscriber(string subscriberName, Channel* ch){
        name=subscriberName;
        channel=ch;
    }
    void update() override{
        cout<<"Subscriber: "<<name<<" notified about new video."<<channel->getLastVideo()<<endl;
    }
};

int main(){
    Channel*channel=new Channel("TechReviews");
    Subscriber* subscriber1=new Subscriber("Alice",channel);
    Subscriber* subscriber2=new Subscriber("Bob",channel);
    channel->subscribe(subscriber1);
    channel->subscribe(subscriber2);
    channel->uploadVideo("Top 10 Gadgets of 2024");
    channel->unsubscribe(subscriber1);
    channel->uploadVideo("Best Laptops for Programming");
    return 0;
}