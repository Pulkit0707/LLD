#include <bits/stdc++.h>
using namespace std;

class DocumentElement{
    public: 
    virtual string render()=0;
};

class TextElement: public DocumentElement{
    private: string text;
    public:
    TextElement(string t){
        text = t;
    }
    string render() override{
        return text;
    }
};

class ImageElement: public DocumentElement{
    private: string path;
    public:
    ImageElement(string p){
        path = p;
    }
    string render() override{
        return "<img src=\"" + path + "\" />";
    }
};

class Save{
    public:
    virtual void save()=0;
};

class SaveToDB: public Save{
    public:
    void save() override{
        cout << "Saving to Database" << endl;
    }
};

class SaveToFile: public Save{
    public:
    void save() override{
        cout << "Saving to File" << endl;
    }
};

class Document{
    private:
    vector<DocumentElement*> elements;
    public:
    void addElement(DocumentElement* element){
        elements.push_back(element);
    }
    vector<DocumentElement*> getElements(){
        return elements;
    }
};

class DocumentEditor{
    private:
    Document* document;
    Save* saver;
    public:
    DocumentEditor(Document*doc, Save* s){
        document = doc;
        saver = s;
    }
    void addText(string txt){
        document->addElement(new TextElement(txt));
    }
    void addImage(string path){
        document->addElement(new ImageElement(path));
    }
    string renderDocument(){
        return DocumentRenderer().render(document);
    }
    void saveDocument(){
        saver->save();
    }
};

class DocumentRenderer{
    public:
    string render(Document* doc){
        vector<DocumentElement*> elements = doc->getElements();
        string result;
        for(auto element: elements){
            result += element->render() + "\n";
        }
    }
};

int main(){
    Document*doc = new Document();
    Save* saver = new SaveToFile();
    DocumentEditor editor(doc, saver);

    editor.addText("Hello, World!");
    editor.addImage("image.png");   
    cout << editor.renderDocument();
    editor.saveDocument();
    return 0;
}