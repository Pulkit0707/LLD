#include <bits/stdc++.h>
#include "App.h"
#include "models/User.h"
#include "models/Restraunt.h"
using namespace std;

int main(){ 
    App*app=new App();
    User*user=new User("Main","Ghar");
    vector<Restraunt>restraunts=app->search("Dharti");
    //any other ops
    return 0;
}