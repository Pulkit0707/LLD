#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include "Cart.h"
using namespace std;

class User{
    private:
    string name;
    static int nextUserId;
    int id;
    string address;
    Cart cart;
    public:
    User(const string& name, const string& address)
        : name(name), address(address), id(nextUserId++) {}
    string getName() const {
        return name;
    }
    int getId() const {
        return id;
    }
    string getAddress() const {
        return address;
    }
    Cart getCart() {
        return cart;
    }
};

int User::nextUserId = 1;

#endif // USER_H