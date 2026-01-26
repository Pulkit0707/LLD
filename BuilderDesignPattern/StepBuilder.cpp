#include <bits/stdc++.h>
using namespace std;

class HttpReq{
    private:
    string url;
    string method;
    map<string,string>headers;
    map<string,string>queryParams;
    string body;
    int timeout;
    //private constructor
    HttpReq(){}
    public:
    friend class HttpReqBuilder;
    void execute(){
        cout<<"Executing "<<method<<" request to "<<url<<endl;
        if(!queryParams.empty()){
            cout<<"Query Parametes"<<endl;
            for(auto &x:queryParams){
                cout<<x.first<<" : "<<x.second<<endl;
            }
        }
        cout<<"Headers: "<<endl;
        for(auto &x:headers){
            cout<<x.first<<" : "<<x.second<<endl;
        }
        if(!body.empty()){
            cout<<"Body: "<<body<<endl;
        }
        cout<<"Timeout: "<<timeout<<" seconds"<<endl;
        cout<<"Request executed successfully"<<endl;
    }
};

class MethodStep;
class HeaderStep;
class OptionalStep;

class UrlStep{
    public:
    virtual MethodStep&withUrl(const string&url)=0;
};

class MethodStep{
    public:
    virtual HeaderStep&withMethod(const string &method)=0;
};

class HeaderStep{
    public:
    virtual OptionalStep&withHeader(const string &key,const string &value)=0;
};

class OptionalStep{
    public:
    virtual ~OptionalStep(){}
    virtual OptionalStep&withBody(const string&body)=0;
    virtual OptionalStep&withQueryParam(const string &key,const string &value)=0;
    virtual OptionalStep&withTimeout(int t)=0;
    virtual HttpReq build()=0;
};

class HttpReqBuilder:
    public UrlStep,
    public MethodStep,
    public HeaderStep,
    public OptionalStep{
    private:
    HttpReq req;
    public:
    MethodStep&withUrl(const string &u) override{
        req.url=u;
        return *this;
    }
    HeaderStep&withMethod(const string &m) override{
        req.method=m;
        return *this;
    }
    OptionalStep&withHeader(const string &key,const string &val) override{
        req.headers[key]=val;
        return *this;
    }
    OptionalStep&withBody(const string &b) override{
        req.body=b;
        return *this;
    }
    OptionalStep&withQueryParam(const string &key,const string &val) override{
        req.queryParams[key]=val;
        return *this;
    }
    OptionalStep&withTimeout(int t) override{
        req.timeout=t;
        return *this;
    }
    HttpReq build() override{
        if(req.url.empty()){
            throw runtime_error("URL cannot be empty");
        }
        return req;
    }
    static UrlStep& create(){
        return *(new HttpReqBuilder());
    }
};

int main(){
    HttpReq req=HttpReqBuilder::create()
        .withUrl("http://example.com/api/data")
        .withMethod("POST")
        .withHeader("Content-Type","application/json")
        .withQueryParam("userId","12345")
        .withBody("{\"name\":\"John Doe\",\"age\":30}")
        .withTimeout(10)
        .build();
    req.execute();
    return 0;
}