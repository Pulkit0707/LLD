#include <bits/stdc++.h>
using namespace std;

//====================================================
// Product
//====================================================

class Product {
public:
    string name;
    int price;
    string desc;

    Product() {}

    Product(string name, int price, string desc)
        : name(name), price(price), desc(desc) {}

    void show() {
        cout << "Name : " << name << endl;
        cout << "Price : " << price << endl;
        cout << "Description : " << desc << endl;
    }
};

//====================================================
// Builder
//====================================================

class ProductBuilder {

    string name;
    int price;
    string desc;

public:

    ProductBuilder& setName(string name) {
        this->name = name;
        return *this;
    }

    ProductBuilder& setPrice(int price) {
        this->price = price;
        return *this;
    }

    ProductBuilder& setDesc(string desc) {
        this->desc = desc;
        return *this;
    }

    Product build() {
        return Product(name, price, desc);
    }
};

//====================================================
// Store
//====================================================

class Store {

    unordered_map<string, pair<Product,int>> inventory;

public:

    void addProduct(Product product,int quantity) {

        inventory[product.name] = {product,quantity};
    }

    int getStock(string productName) {

        return inventory[productName].second;
    }

    void reduceStock(string productName,int quantity) {

        inventory[productName].second -= quantity;
    }

    Product getProduct(string productName) {

        return inventory[productName].first;
    }
};

//====================================================
// Cart
//====================================================

class Cart {

    unordered_map<string,int> products;

public:

    void addProduct(Product product) {

        products[product.name]++;
    }

    unordered_map<string,int> getProducts() {

        return products;
    }
};

//====================================================
// Forward Declaration
//====================================================

class Order;

//====================================================
// State
//====================================================

class OrderState {

public:

    virtual void track(Order* order)=0;

    virtual ~OrderState()=default;
};

class PackagingState;
class PickedUpState;
class DeliveredState;

extern PackagingState packaging;
extern PickedUpState pickedUp;
extern DeliveredState delivered;

//====================================================
// Order
//====================================================

class Order {

    OrderState* state;

    unordered_map<string,int> products;

    Store* store;

public:

    Order(Store* store)
        : state(nullptr),
          store(store) {}

    void setState(OrderState* state) {

        this->state = state;
    }

    void placeOrder(Cart& cart) {

        products = cart.getProducts();

        for(auto product : products){

            if(store->getStock(product.first) < product.second){

                throw runtime_error(
                    "Insufficient Stock for " + product.first);
            }

            store->reduceStock(product.first,
                               product.second);
        }

        cout<<"Order Placed Successfully\n";

        setState((OrderState*)&packaging);
    }

    void track() {

        state->track(this);
    }
};

//====================================================
// States
//====================================================

class PackagingState : public OrderState {

public:

    void track(Order* order) override {

        cout<<"Packaging Order...\n";

        order->setState((OrderState*)&pickedUp);
    }
};

class PickedUpState : public OrderState {

public:

    void track(Order* order) override {

        cout<<"Order Picked Up\n";

        order->setState((OrderState*)&delivered);
    }
};

class DeliveredState : public OrderState {

public:

    void track(Order*) override {

        cout<<"Order Delivered\n";
    }
};

PackagingState packaging;
PickedUpState pickedUp;
DeliveredState delivered;

//====================================================
// Order Service
//====================================================

class OrderService {

    Store* store;

public:

    OrderService(Store* store)
        : store(store) {}

    Order* createOrder(Cart& cart){

        Order* order = new Order(store);

        order->placeOrder(cart);

        return order;
    }
};

//====================================================
// Main
//====================================================

int main(){

    Product apple =
        ProductBuilder()
        .setName("Apple")
        .setPrice(100)
        .setDesc("Fresh Apples")
        .build();

    Product milk =
        ProductBuilder()
        .setName("Milk")
        .setPrice(60)
        .setDesc("Amul Milk")
        .build();

    Store store;

    store.addProduct(apple,10);
    store.addProduct(milk,20);

    Cart cart;

    cart.addProduct(apple);
    cart.addProduct(milk);

    OrderService orderService(&store);

    Order* order = orderService.createOrder(cart);

    cout << endl;

    order->track();

    order->track();

    order->track();

    return 0;
}