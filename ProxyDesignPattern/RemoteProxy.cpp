#include <bits/stdc++.h>
using namespace std;

class IService{
    public:
    virtual void fetch()=0;
};

class DataService: public IService{
    public:
    void fetch() override{
        cout<<"fetching data"<<endl;
    }
};

class DataProxy:public IService{
    DataService *ds;
    public:
    DataProxy(){
        ds=nullptr;
    }
    void fetch() override{
        if(ds==nullptr) {
            cout<<"connecting to remote server"<<endl;
            ds=new DataService();
        }
        ds->fetch();
    }
};

int main(){
    IService*client=new DataProxy();
    client->fetch();
    return 0;
}