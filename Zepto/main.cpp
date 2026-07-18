#include <bits/stdc++.h>
using namespace std;

//==================================================
// Product
//==================================================

class Product {
public:
    string name;
    int price;
    string desc;

    Product() {}

    Product(string name, int price, string desc)
        : name(name), price(price), desc(desc) {}

    void show() {
        cout << name << " | " << price << " | " << desc << endl;
    }
};

//==================================================
// Builder
//==================================================

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

//==================================================
// Store
//==================================================

class Store {

    unordered_map<string, pair<Product,int>> inventory;

public:

    void addProduct(Product product,int quantity){
        inventory[product.name]={product,quantity};
    }

    int getStock(string name){
        return inventory[name].second;
    }

    void reduceStock(string name,int quantity){
        inventory[name].second-=quantity;
    }
};

//==================================================
// Cart
//==================================================

class Cart{

    unordered_map<string,int> products;

public:

    void addProduct(Product product){
        products[product.name]++;
    }

    unordered_map<string,int> getProducts(){
        return products;
    }
};

//==================================================
// Forward Declaration
//==================================================

class Order;

//==================================================
// State Pattern
//==================================================

class OrderState{

public:

    virtual void track()=0;

    virtual void next(Order* order)=0;

    virtual ~OrderState()=default;
};

class PackagingState;
class PickedUpState;
class DeliveredState;

extern PackagingState packaging;
extern PickedUpState pickedUp;
extern DeliveredState delivered;

//==================================================
// Order
//==================================================

class Order{

    OrderState* state;

    Store* store;

    unordered_map<string,int> products;

public:

    Order(Store* store)
        : store(store),state(nullptr){}

    void setState(OrderState* state){
        this->state=state;
    }

    void placeOrder(Cart& cart){

        products=cart.getProducts();

        for(auto product:products){

            if(store->getStock(product.first)<product.second){
                throw runtime_error("Insufficient Stock");
            }

            store->reduceStock(product.first,product.second);
        }

        cout<<"Order Placed Successfully\n";

        setState(&packaging);
    }

    void track(){

        state->track();
    }

    void updateStatus(){

        state->next(this);
    }
};

//==================================================
// Packaging State
//==================================================

class PackagingState : public OrderState{

public:

    void track() override{

        cout<<"Current Status : Packaging\n";
    }

    void next(Order* order) override{

        cout<<"Packaging Finished\n";

        order->setState(&pickedUp);
    }
};

//==================================================
// Picked Up State
//==================================================

class PickedUpState : public OrderState{

public:

    void track() override{

        cout<<"Current Status : Picked Up\n";
    }

    void next(Order* order) override{

        cout<<"Order Picked By Delivery Partner\n";

        order->setState(&delivered);
    }
};

//==================================================
// Delivered State
//==================================================

class DeliveredState : public OrderState{

public:

    void track() override{

        cout<<"Current Status : Delivered\n";
    }

    void next(Order*) override{

        cout<<"Already Delivered\n";
    }
};

//==================================================
// Global State Objects
//==================================================

PackagingState packaging;
PickedUpState pickedUp;
DeliveredState delivered;

//==================================================
// Order Service
//==================================================

class OrderService{

    Store* store;

public:

    OrderService(Store* store)
        : store(store){}

    Order* createOrder(Cart& cart){

        Order* order=new Order(store);

        order->placeOrder(cart);

        return order;
    }
};

//==================================================
// Main
//==================================================

int main(){

    Product apple=
        ProductBuilder()
        .setName("Apple")
        .setPrice(100)
        .setDesc("Fresh Apples")
        .build();

    Product milk=
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

    OrderService service(&store);

    Order* order=service.createOrder(cart);

    cout<<"\n";

    order->track();

    cout<<"\n";

    order->updateStatus();

    order->track();

    cout<<"\n";

    order->updateStatus();

    order->track();

    cout<<"\n";

    order->updateStatus();
}