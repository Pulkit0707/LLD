#include <bits/stdc++.h>
using namespace std;

class Document{
    private:
    vector<string> elements;
    string renderDoc;
    public:
    void addText(string text){
        elements.push_back(text);
    }
    void addImage(string path){
        elements.push_back(path);
    }
    string renderDoc(){
        if(renderDoc.empty()){
            string ans;
            for(auto x:elements){
                if(x.size()>4 and (x.substr(x.size()-4)=="'png" or x.substr(x.size()-4)==".jpg")){
                    ans+="[Image:"+x+"]\n";
                }
                else{
                    ans+=x+"\n";
                }
            }
            renderDoc=ans;
        }
        return renderDoc;
    }
    void saveToFile(){
        ofstream file("doc.txt");
        if(file.is_open()){
            file<<renderDoc();
            file.close();
            cout<<"Document saved to doc.txt\n";
        }
        else{
            cout<<"Error opening file!\n";
        }
    }
};

int main(){
    Document doc;
    doc.addText("Hello, this is a sample document.");
    doc.addImage("image1.png");
    doc.addText("This document contains text and images.");
    doc.addImage("photo.jpg");
    cout<<doc.renderDoc();
    doc.saveToFile();
    return 0;
}