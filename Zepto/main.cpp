#include <bits/stdc++.h>
using namespace std;

class Product{
    public:
    string name;
    int price;
    string desc;
    Product(string name,int price,string desc) : name(name),price(price),desc(desc) {}
    void show(){
        cout<<"Name: "<<name<<endl;
        cout<<"Price: "<<price<<endl;
        cout<<"Description: "<<desc<<endl;
    }
    void addToCart(Cart &cart){
        cart.addProduct(*this);
    }
};

class ProductBuilder{
    string name;
    int price;
    string desc;
    public:
    ProductBuilder& setName(string name){
        this->name=name;
        return *this;
    }
    ProductBuilder &setPrice(int price){
        this->price=price;
        return *this;
    }
    ProductBuilder &setDesc(string desc){
        this->desc=desc;
        return *this;
    }
    Product build(){
        return Product(name,price,desc);
    }
};

class Store{
    unordered_map<Product,int>products;
    public:
    Store(unordered_map<Product,int> products):products(products){}
    void refill(unordered_map<Product,int> products){
        for(auto product:products){
            this->products[product.first]+=product.second;
        }
    }
    int getStock(Product product){
        return products[product];
    }
    void reduceStock(Product product,int quantity){
        products[product]-=quantity;
    }
};

class Cart{
    unordered_map<Product,int> products;
    public:
    void addProduct(Product product){
        products[product]++;
    }
    unordered_map<Product,int> getProducts(){
        return products;
    }
};

class Order;

class OrderState{
    public:
    virtual void track(Order* order)=0;
};

class PackagingState;
class PickedUpState;
class DeliveredState;

extern PackagingState packagingState;
extern PickedUpState pickedUpState;
extern DeliveredState deliveredState;

class Order{
    OrderState* state;
    unordered_map<Product,int>products;
    Store store;
    public:
    Order(OrderState* state,Store* store):state(state),store(store){}
    void setState(OrderState* state){
        this->state=state;
    }
    void placeOrder(Cart &cart){
        products=cart.getProducts();
        for(auto product:products){
            if(store.getStock(product.first)<product.second){
                throw runtime_error("Insufficient stock for product: "+product.first.name);
            }
            store.reduceStock(product.first,product.second);
        }
        this->setState(&packagingState);
    }
    void track(){
        state->track(this);
    }
};

class PackagingState:public OrderState{
    public:
    void track(Order* order){
        cout<<"Your order is being packaged"<<endl;
        order->setState(&pickedUpState);
    }
};

class PickedUpState:public OrderState{
    public:
    void track(Order* order){
        cout<<"Your order has been picked up"<<endl;
        order->setState(&deliveredState);
    }
};

class DeliveredState:public OrderState{
    public:
    void track(Order* order){
        cout<<"Your order has been delivered"<<endl;
    }
};

PackagingState packagingState;
PickedUpState pickedUpState;
DeliveredState deliveredState;

int main(){
    
}