#ifndef UPI_H
#define UPI_H

#include <bits/stdc++.h>
#include "PaymentStrategy.h"
using namespace std;

class UPI:public PaymentStrategy{
    public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using UPI." << endl;
    }
};

#endif // UPI_H