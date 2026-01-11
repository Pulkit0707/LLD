#ifndef CART_H
#define CART_H

#include <bits/stdc++.h>
#include "MenuItem.h"
#include "Restraunt.h"
using namespace std;

class Cart{
    private:
    Restraunt*r;
    vector<MenuItem> items;
    public:
    void addToCart(MenuItem it){
        items.push_back(it);
    }
    double totalPrice(){
        double total=0;
        for(auto it:items){
            total+=it.getPrice();
        }
        return total;
    }
    bool isEmpty(){
        return items.size()==0;
    }
    void setRestraunt(Restraunt* restraunt){
        r=restraunt;
    }
    Restraunt getRestraunt(){
        return *r;
    }
};

#endif // CART_H