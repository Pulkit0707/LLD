#include <bits/stdc++.h>
using namespace std;

class IVisitor{
    public:
    virtual void visit(class TxtFile &file)=0;
    virtual void visit(class ImgFile &file)=0;
    virtual void visit(class VidFile &file)=0;
};

class SizeVistor:public IVisitor{
    public:
    void visit(TxtFile& f) override{
        cout<<"Calculating size of TxtFile"<<endl;
    }
    void visit(ImgFile& f) override{
        cout<<"Calculating size of ImgFile"<<endl;
    }
    void visit(VidFile& f) override{
        cout<<"Calculating size of VidFile"<<endl;
    }
};

class CompressVistor:public IVisitor{
    public:
    void visit(TxtFile& f) override{
        cout<<"Compressing TxtFile"<<endl;
    }
    void visit(ImgFile& f) override{
        cout<<"Compressing ImgFile"<<endl;
    }
    void visit(VidFile& f) override{
        cout<<"Compressing VidFile"<<endl;
    }
};

class Document{
    public:
    virtual void accept(IVisitor &v)=0;
};

class TxtFile:public Document{
    public:
    void accept(IVisitor &v) override{
        v.visit(*this);
    }
};

class ImgFile:public Document{
    public:
    void accept(IVisitor &v) override{
        v.visit(*this);
    }
};

class VidFile:public Document{
    public:
    void accept(IVisitor &v) override{
        v.visit(*this);
    }
};

int main(){
    Document*doc1=new TxtFile();
    Document*doc2=new ImgFile();
    Document*doc3=new VidFile();
    IVisitor*sz=new SizeVistor();
    IVisitor*cp=new CompressVistor();
    doc1->accept(*sz);
    doc2->accept(*cp);
    return 0;
}