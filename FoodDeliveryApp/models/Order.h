#ifndef ORDER_H
#define ORDER_H

#include <bits/stdc++.h>
#include "User.h"
#include "Restraunt.h"
#include "MenuItem.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class Order{
    private:
    static int nextOrderId;
    int id;
    User user;
    Restraunt*r;
    vector<MenuItem> items;
    PaymentStrategy*strategy;
    public:
    Order(const User& u, Restraunt* res, const vector<MenuItem>& its, PaymentStrategy* ps)
        : user(u), r(res), items(its), strategy(ps), id(nextOrderId++) {}
    virtual int getType()=0;
};

int Order::nextOrderId = 1;

#endif // ORDER_H