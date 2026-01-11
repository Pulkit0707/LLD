#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include <bits/stdc++.h>
#include "../models/Order.h"
#include "../models/User.h"
#include "../models/Cart.h"
#include "../models/Restraunt.h"
#include "../models/MenuItem.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class OrderFactory{
    public:
    virtual Order* createOrder(User*user, Cart*cart, Restraunt*restraunt, const vector<MenuItem>&menuItems, PaymentStrategy*paymentStrategy, const string &type)=0;
    virtual ~OrderFactory(){}
};

#endif // ORDER_FACTORY_H