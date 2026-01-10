#include <bits/stdc++.h>
using namespace std;

class CPU{
    public:
    void process(){
        cout<<"CPU processing..."<<endl;
    }
};

class Memory{
    public:
    void load(){
        cout<<"Loading data into memory..."<<endl;
    }
};

class HardDrive{
    public:
    void read(){
        cout<<"Reading data from hard drive..."<<endl;
    }
};

class PowerSupply{
    public:
    void supplyPower(){
        cout<<"Supplying power to components..."<<endl;
    }
};

class Facade{
    CPU*cpu;
    Memory*memory;
    HardDrive*hardDrive;
    PowerSupply*powerSupply;
    public:
    Facade(CPU*cpu,Memory*memory,HardDrive*hardDrive,PowerSupply*powerSupply)
    :cpu(cpu),memory(memory),hardDrive(hardDrive),powerSupply(powerSupply){}
    void execute(){
        cout<<"Executing complex operations..."<<endl;
        powerSupply->supplyPower();
        cpu->process(); 
        memory->load();
        hardDrive->read();
    }
};

class Computer{
    Facade*facade;
    public:
    Computer(Facade*facade):facade(facade){}
    void startComputer(){
        cout<<"Computer Started"<<endl;
        facade->execute();
    }
};

int main(){
    CPU*cpu=new CPU();
    Memory*memory=new Memory();
    HardDrive*hardDrive=new HardDrive();
    PowerSupply*powerSupply=new PowerSupply();
    Facade*facade=new Facade(cpu,memory,hardDrive,powerSupply);
    Computer*computer=new Computer(facade);
    computer->startComputer();
    return 0;
}