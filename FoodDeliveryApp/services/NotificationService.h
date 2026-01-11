#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <bits/stdc++.h>
#include "../models/Order.h"
using namespace std;

class NotificationService{
    public:
    void notifyUser(Order*order){
        cout<<"sending notification with following details"<<order->getItems()<<" "<<order->getRestraunt()->getName()<<endl;
    }
};

#endif // NOTIFICATION_SERVICE_H