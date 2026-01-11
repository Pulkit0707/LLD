#ifndef NOW_ORDER_FACTORY_H
#define NOW_ORDER_FACTORY_H

#include <bits/stdc++.h>
#include "OrderFactory.h"
using namespace std;

class NowOrderFactory:public OrderFactory{
    public:
    void createOrder() override {
        cout << "Immediate Order Created." << endl;
    }
};

#endif // NOW_ORDER_FACTORY_H