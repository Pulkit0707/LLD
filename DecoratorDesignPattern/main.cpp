#include <bits/stdc++.h>
using namespace std;

class Character{
    public:
    virtual void getAbilities()=0;
    virtual ~Character(){}
};

class Mario: public Character{
    public:
    void getAbilities() override{
        cout<<"Base Mario Abilities"<<endl;
    }
};

class Decorator: public Character{
    protected:
    Character*character;
    public:
    Decorator(Character*character){
        this->character=character;
    }
};

class HeightUpDecorator: public Decorator{
    public:
    HeightUpDecorator(Character*character): Decorator(character){}
    void getAbilities() override{
        character->getAbilities();
        cout<<"Height Up Ability Added!"<<endl;
    }
};

class SpeedUpDecorator: public Decorator{
    public:
    SpeedUpDecorator(Character*character): Decorator(character){}
    void getAbilities() override{
        character->getAbilities();
        cout<<"Speed Up Ability Added!"<<endl;
    }
};

class StrengthUpDecorator: public Decorator{
    public:
    StrengthUpDecorator(Character*character): Decorator(character){}
    void getAbilities() override{
        character->getAbilities();
        cout<<"Strength Up Ability Added!"<<endl;
    }
};

int main(){
    Character* mario=new Mario();
    cout<<"Mario Abilities:"<<endl;
    mario->getAbilities();
    cout<<endl;
    mario=new HeightUpDecorator(mario);
    cout<<"Mario Abilities after Height Up:"<<endl; 
    mario->getAbilities();
    cout<<endl;
    mario=new SpeedUpDecorator(mario);
    cout<<"Mario Abilities after Speed Up:"<<endl;
    mario->getAbilities();
    cout<<endl;
    mario=new StrengthUpDecorator(mario);
    cout<<"Mario Abilities after Strength Up:"<<endl;
    mario->getAbilities();
    cout<<endl;
    delete mario;
    return 0;
}