#include <bits/stdc++.h>
using namespace std;

class IDisplay{
    public:
    virtual void display(string path)=0;
};

class ImageDisplay: public IDisplay{
    public:
    void display(string path) override{
        cout<<"performing expensive operations"<<endl;
        cout<<"displaying image at path "<<path<<endl;
    }
};

class ImageProxy:public IDisplay{
    ImageDisplay *ds;
    public:
    ImageProxy(){
        ds=nullptr;
    }
    void display(string path) override{
        if(ds==nullptr) ds=new ImageDisplay();
        ds->display(path);
    }
};

int main(){
    IDisplay *client=new ImageProxy();
    client->display("image path");
    return 0;
}