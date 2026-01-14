#include <bits/stdc++.h>
using namespace std;

class FileSystemItem{
    public:
    virtual void ls()=0;
    virtual void openAll()=0;
    virtual int getSize()=0;
    virtual string getName()=0;
    virtual FileSystemItem* cd(const string&name)=0;
    virtual bool isFolder()=0;
};

class File: public FileSystemItem{
    string name;
    int size;
    public:
    File(string s,int sz){
        name=s;
        size=sz;
    }
    bool isFolder() override{
        return 0;
    }
    void ls() override{
        cout<<name<<endl;
    }
    void openAll() override{
        cout<<"Opening file "<<name<<endl;
    }
    int getSize() override{
        return size;
    }
    string getName() override{
        return name;
    }
    FileSystemItem*cd(const string&s) override{
        return nullptr;
    }
};

class Folder: public FileSystemItem{
    string name;
    vector<FileSystemItem*>list;
    public:
    Folder(string s){
        name=s;
    }
    void add(FileSystemItem*item){
        list.push_back(item);
    }
    bool isFolder() override{
        return 1;
    }
    string getName() override{
        return name;
    }
    int getSize() override{
        int ans=0;
        for(auto &x:list) ans+=x->getSize();
        return ans;
    }
    void ls() override{
        cout<<name<<endl;
        for(auto &x:list) x->ls();
    }
    void openAll() override{
        for(auto &x:list) x->openAll();
    }
    FileSystemItem*cd(const string&s) override{
        for(auto &x:list){
            if(x->isFolder() and x->getName()==s){
                return x;
            }
        }
        return nullptr;
    }
};

int main(){
    Folder*root=new Folder("root");
    root->add(new File("file1",2));
    root->add(new File("file2",3));
    Folder*images=new Folder("images");
    images->add(new File("img1",5));
    root->add(images);
    cout<<root->getSize()<<endl;
    root->cd("images");
    return 0;
}