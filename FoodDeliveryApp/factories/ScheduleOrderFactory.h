#ifndef SCHEDULE_ORDER_FACTORY_H
#define SCHEDULE_ORDER_FACTORY_H

#include <bits/stdc++.h>
#include "OrderFactory.h"
using namespace std;

class ScheduleOrderFactory:public OrderFactory{
    string scheduledTime;
    public:
    ScheduleOrderFactory(string scheduledTime) : scheduledTime(scheduledTime) {}
    void createOrder() override {
        cout << "Scheduled Order Created for time: " << scheduledTime << endl;
    }
};

#endif // SCHEDULE_ORDER_FACTORY_H