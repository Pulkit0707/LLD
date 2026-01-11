#ifndef CARD_H
#define CARD_H

#include <bits/stdc++.h>
#include "PaymentStrategy.h"
using namespace std;

class Card:public PaymentStrategy{
    public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using Card." << endl;
    }
};

#endif // CARD_H