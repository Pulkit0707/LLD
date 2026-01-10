#include <bits/stdc++.h>
using namespace std;

class Client{
    public:
    void getReport(Reports*report){
        cout<<report->getData()<<endl;
    }
};

class Reports{
    public:
    virtual string getData()=0;
};

class XMLDataAdapter: public Reports{
    XMLData*data;
    public:
    XMLDataAdapter(XMLData* d):data(d){}
    string getData() override{
        string xmlData=data->getXMLData();
        return "Adapted: "+xmlData;
    }
};

class XMLData{
    public:
    string getXMLData(){
        return "XML Data";
    }
};

int main(){
    Client*client=new Client();
    XMLData*xmlData=new XMLData();
    Reports*report=new XMLDataAdapter(xmlData);
    client->getReport(report);
    return 0; 
}