#ifndef RESTRAUNT_H
#define RESTRAUNT_H

#include <bits/stdc++.h>
#include "MenuItem.h"
using namespace std;

class Restraunt{
    private:
    static int nextRestaurantId;
    int restaurantId;
    string name;
    string location;
    vector<MenuItem> menu;
    public:
    Restraunt(const string& name, const string& location)
        : name(name), location(location), restaurantId(nextRestaurantId++) {}
    ~Restraunt() {
        menu.clear();
    }
    string getName() const {
        return name;
    }
    string getLocation() const {
        return location;
    }
    int getRestaurantId() const {
        return restaurantId;
    }
    string setName(const string& newName) {
        name = newName;
    }
    string setLocation(const string& newLocation) {
        location = newLocation;
    }
};

int Restraunt::nextRestaurantId = 1;

#endif // RESTRAUNT_H