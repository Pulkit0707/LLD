#ifndef SCHEDULE_ORDER_FACTORY_H
#define SCHEDULE_ORDER_FACTORY_H

#include <bits/stdc++.h>
#include "OrderFactory.h"
#include "../models/Order.h"
#include "../models/User.h"
#include "../models/Cart.h"
#include "../models/Restraunt.h"
#include "../models/MenuItem.h"
#include "../strategies/PaymentStrategy.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
using namespace std;

class ScheduleOrderFactory:public OrderFactory{
    string scheduledTime;
    public:
    ScheduleOrderFactory(string scheduledTime) : scheduledTime(scheduledTime) {}
    Order* createOrder(User*user, Cart*cart, Restraunt*restraunt, const vector<MenuItem>&menuItems, PaymentStrategy*paymentStrategy, const string &type) override {
        Order*order=nullptr;
        if(type=="Delivery"){
            auto deliveryOrder=new DeliveryOrder(user,restraunt,menuItems,paymentStrategy,user->getAddress());
            order=deliveryOrder;
        }
        else{
            auto pickUpOrder=new PickupOrder(user,restraunt,menuItems,paymentStrategy,user->getAddress());
            order=pickUpOrder;
        }
        return order;
    }
};

#endif // SCHEDULE_ORDER_FACTORY_H