#ifndef APP_H
#define APP_H

#include <bits/stdc++.h>
#include "models/MenuItem.h"
#include "models/Restraunt.h"
#include "managers/RestrauntManager.h"
#include "models/Cart.h"
#include "models/User.h"
#include "models/Order.h"
#include "strategies/PaymentStrategy.h"
using namespace std;

class App{
    public:
    App(){
        initializeRestraunts();
    }
    void initializeRestraunts(){
        Restraunt*r1=new Restraunt("Veg", "Duniya");
        r1->addMenuItem(MenuItem("MixVeg",101,"abc"));
        Restraunt*r2=new Restraunt("Non Veg", "Dharti");
        r2->addMenuItem(MenuItem("Chicken",103,"def"));
        RestrauntManager*restrauntManager=RestrauntManager::getInstance();
        restrauntManager->addRestaurant(*r1);
        restrauntManager->addRestaurant(*r2);
    }
    vector<Restraunt> search(const string&location){
        return RestrauntManager::getInstance()->searchByLocation(location);
    }
    void selectRestraunt(User *user, Restraunt*restraunt){
        Cart cart=user->getCart();
        cart.setRestraunt(restraunt);
    }
    void addToCart(User*user,MenuItem item){
        Restraunt r=user->getCart().getRestraunt();
        user->getCart().addToCart(item);
    }
    void checkout(User*user, PaymentStrategy*ps){
        ps->pay(user->getCart().totalPrice());
    }
};

#endif //APP_H