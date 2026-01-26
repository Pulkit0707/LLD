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

class HttpReqBuilder{
    private:
    HttpReq req;
    public:
    HttpReqBuilder& withUrl(const string &u){
        req.url=u;
        return *this;
    }
    HttpReqBuilder& withMethod(const string &m){
        req.method=m;
        return *this;
    }
    HttpReqBuilder& withQueryParam(const string &key,const string &val){
        req.queryParams[key]=val;
        return *this;
    }
    HttpReqBuilder& withHeader(const string &key,const string &val){
        req.headers[key]=val;
        return *this;
    }
    HttpReqBuilder& withBody(const string &b){
        req.body=b;
        return *this;
    }
    HttpReqBuilder& withTimeout(int t){
        req.timeout=t;
        return *this;
    }
    HttpReq build(){
        if(req.url.empty()){
            throw runtime_error("URL cannot be empty");
        }
        return req;
    }
};

class HttpReqDirector{
    public:
    static HttpReq createGetReq(const string &url){
        return HttpReqBuilder()
             .withUrl(url)
             .withMethod("GET")
             .build();
    }
    static HttpReq createJsonPostReq(const string&url,const string &body){
        return HttpReqBuilder()
               .withUrl(url)
               .withMethod("POST")
               .withHeader("Content-Type","application/json")
               .withBody(body)
               .build();
    }
};

int main(){
    HttpReq normalReq=HttpReqBuilder()
        .withUrl("http://example.com/api/data")
        .withMethod("POST")
        .withHeader("Content-Type","application/json")
        .withQueryParam("userId","12345")
        .withBody("{\"name\":\"John Doe\",\"age\":30}")
        .withTimeout(10)
        .build();
    normalReq.execute();
    HttpReq getReq=HttpReqDirector::createGetReq("http://example.com/api/info");
    getReq.execute();
    HttpReq postReq=HttpReqDirector::createJsonPostReq("http://example.com/api/submit","{\"data\":\"sample\"}");
    postReq.execute();
    return 0;
}