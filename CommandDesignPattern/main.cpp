#include <bits/stdc++.h>
using namespace std;

class Command{
    public:
    virtual void execute()=0;
    virtual void undo()=0;
    virtual ~Command(){}
};

class Light{
public:
    void on(){
        cout<<"Light is On"<<endl;
    }
    void off(){
        cout<<"Light is Off"<<endl;
    }
};

class Fan{
public:
    void start(){
        cout<<"Fan is Started"<<endl;
    }
    void stop(){
        cout<<"Fan is Stopped"<<endl;
    }
};

class LightCommand:public Command{
    Light*light;
    public:
    LightCommand(Light* l):light(l){}
    void execute() override{
        light->on();
    }
    void undo() override{
        light->off();
    }
};

class FanCommand:public Command{
    Fan*fan;
    public:
    FanCommand(Fan* f):fan(f){}
    void execute() override{
        fan->start();
    }
    void undo() override{
        fan->stop();
    }
};

class RemoteControl{
    vector<Command*>commands;
    vector<bool>status;
    public:
    void setCommand(Command* command){
        commands.push_back(command);
        status.push_back(false);
    }
    void pressButton(int index){
        if(index<commands.size()){
            if(!status[index]){
                commands[index]->execute();
                status[index]=true;
            }else{
                commands[index]->undo();
                status[index]=false;
            }
        }
    }
};


int main(){
    Light* light=new Light();
    Fan* fan=new Fan();

    RemoteControl* remote=new RemoteControl();

    remote->setCommand(new LightCommand(light));
    remote->setCommand(new FanCommand(fan));

    cout<<"Pressing Light Button:"<<endl;
    remote->pressButton(0);
    cout<<"Pressing Fan Button:"<<endl;
    remote->pressButton(1);
    cout<<"Pressing Light Button Again:"<<endl;
    remote->pressButton(0);
    cout<<"Pressing Fan Button Again:"<<endl;
    remote->pressButton(1);
    return 0;
}