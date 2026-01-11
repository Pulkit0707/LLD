#ifndef PICKUP_ORDER_H
#define PICKUP_ORDER_H

#include <bits/stdc++.h>
#include "Order.h"
using namespace std;

class PickupOrder:public Order{
    private:
    string resAddress;
    public:
    PickupOrder(const User& u, Restraunt* res, const vector<MenuItem>& its, PaymentStrategy* ps, const string& addr)
        : Order(u, res, its, ps), resAddress(addr) {}
    int getType() override {
        return 2; // 2 indicates Pickup Order
    }
};

#endif // PICKUP_ORDER_H