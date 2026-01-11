#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include <bits/stdc++.h>
#include "Order.h"
using namespace std;

class DeliveryOrder:public Order{
    private:
    string deliveryAddress;
    public:
    DeliveryOrder(const User& u, Restraunt* res, const vector<MenuItem>& its, PaymentStrategy* ps, const string& addr)
        : Order(u, res, its, ps), deliveryAddress(addr) {}
    int getType() override {
        return 1; // 1 indicates Delivery Order
    }
};

#endif // DELIVERY_ORDER_H