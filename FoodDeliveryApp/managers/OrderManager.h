#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <bits/stdc++.h>
#include "../models/Order.h"
#include "../services/NotificationService.h"
using namespace std;

class OrderManager{
    private:
    vector<Order*> orders;
    static OrderManager* instance;
    OrderManager() {}
    public:
    static OrderManager* getInstance(){
        if(!instance){
            instance=new OrderManager();
        }
        return instance;
    }
    void addOrder(Order* o){
        orders.push_back(o);
    }
    vector<Order*> getOrders(){
        return orders;
    }
};

OrderManager* OrderManager::instance=nullptr;

#endif // ORDER_MANAGER_H