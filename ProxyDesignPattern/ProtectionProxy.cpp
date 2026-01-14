#include <bits/stdc++.h>
using namespace std;

class IDocReader{
    public:
    virtual void unlockPDF(string file,string pwd)=0;
};

class DocReader: public IDocReader{
    public:
    void unlockPDF(string file,string pwd) override{
        cout<<"opening dock with file "<<file<<" and passwrod "<<pwd<<endl;
    }
};

class Proxy:public IDocReader{
    DocReader* dr;
    public:
    Proxy(){
        dr=nullptr;
    }
    void unlockPDF(string path,string pwd) override{
        if(dr==nullptr) dr=new DocReader();
        cout<<"validating client"<<endl;
        dr->unlockPDF(path,pwd);
    }
};

int main(){
    IDocReader*client=new Proxy();
    client->unlockPDF("path","password123");
    return 0;
}