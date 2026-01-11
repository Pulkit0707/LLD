#ifndef MENUITEM_H
#define MENUITEM_H

#include <bits/stdc++.h>
using namespace std;

class MenuItem{
    string name;
    double price;
    string code;
    public:
    MenuItem(string n, double p, string c): name(n), price(p), code(c) {}
    double getPrice() const { return price; }
    string getCode() const { return code; }
    string getName() const { return name; }
    void setName(const string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }    
};

#endif // MENUITEM_H