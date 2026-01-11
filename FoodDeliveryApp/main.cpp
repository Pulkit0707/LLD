#include <bits/stdc++.h>
using namespace std;

class NotificationService{
    public:
    void notifyUser(){}
};

class PaymentStrategy{
    public:
    virtual void pay(double amount)=0;
    virtual ~PaymentStrategy() {}
};

class UPI:public PaymentStrategy{
    public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using UPI." << endl;
    }
};

class Card:public PaymentStrategy{
    public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using Card." << endl;
    }
};

class MenuItem{
    string name;
    double price;
    string code;
    public:
    MenuItem(string n, double p, string c): name(n), price(p), code(c) {}
    double getPrice() const { return price; }
    string getCode() const { return code; }
    string getName() const { return name; }
};

class Restaurant{
    string name;
    string location;
    int id;
    vector<MenuItem> menu;
    public:
    Restaurant(string n, string l, int i): name(n), location(l), id(i) {}
    void addMenuItem(const MenuItem& item) {
        menu.push_back(item);
    }
    const vector<MenuItem>& getMenu() const {
        return menu;
    }
    string getName() const { return name; }
    string getLocation() const { return location; }
    int getId() const { return id; }
};

class RestrauntManager{
    vector<Restaurant> restaurants;
    static RestrauntManager* instance;
    public:
    static RestrauntManager* getInstance(){
        if(!instance){
            instance=new RestrauntManager();
        }
        return instance;
    }
    void addRestaurant(const Restaurant& r){
        restaurants.push_back(r);
    }
    vector<Restaurant> getRestaurants(){
        return restaurants;
    }
    vector<Restaurant> searchByLocation(const string& loc){
        vector<Restaurant> result;
        for(auto& r:restaurants){
            if(r.getLocation()==loc){
                result.push_back(r);
            }
        }
        return result;
    }
};

RestrauntManager* RestrauntManager::instance=nullptr;

class OrderFactory{
    public:
    virtual void createOrder()=0;
    virtual ~OrderFactory() {}
};

class ScheduleOrderFactory:public OrderFactory{
    public:
    void createOrder() override {
        cout << "Scheduled Order Created." << endl;
    }
};

class NowOrderFactory:public OrderFactory{
    public:
    void createOrder() override {
        cout << "Immediate Order Created." << endl;
    }
};

class Cart{
    Restaurant*r;
    vector<MenuItem> items;
    public:
    void addToCart(MenuItem it){
        items.push_back(it);
    }
    int totalPrice(){
        int total=0;
        for(auto it:items){
            total+=it.getPrice();
        }
        return total;
    }
    bool isEmpty(){
        return items.size()==0;
    }  
};

class User{
    string name;
    int id;
    string address;
    Cart cart;
};

class Order{
    int id;
    User user;
    Restaurant*r;
    vector<MenuItem> items;
    PaymentStrategy*strategy;
    public:
    Order(int i, User u, Restaurant* res, vector<MenuItem> its, PaymentStrategy* ps): id(i), user(u), r(res), items(its), strategy(ps) {}
    virtual int getType()=0;
};

class DeliveryOrder:public Order{
    public:
    DeliveryOrder(int i, User u, Restaurant* res, vector<MenuItem> its, PaymentStrategy* ps): Order(i, u, res, its, ps) {}
    int getType() override {
        return 1; // Delivery
    }
};

class DineInOrder:public Order{
    public:
    DineInOrder(int i, User u, Restaurant* res, vector<MenuItem> its, PaymentStrategy* ps): Order(i, u, res, its, ps) {}
    int getType() override {
        return 2; // Dine-In
    }
};

class OrderManager{
    vector<Order*> orders;
    static OrderManager* instance;
    NotificationService notifier;
    public:
    static OrderManager* getInstance(){
        if(!instance){
            instance=new OrderManager();
        }
        return instance;
    }
    void addOrder(Order* o){
        orders.push_back(o);
        notifier.notifyUser();
    }
    vector<Order*> getOrders(){
        return orders;
    }
};

OrderManager* OrderManager::instance=nullptr;

int main(){
    return 0;
}