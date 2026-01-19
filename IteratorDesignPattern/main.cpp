#include <bits/stdc++.h>
using namespace std;

/* Forward declaration */
template<typename T>
class Iterator;

/* Iterable interface */
template<typename T>
class Iterable {
public:
    virtual Iterator<T>* getIterator() = 0;
    virtual ~Iterable() = default;
};

/* Iterator interface */
template<typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() = default;
};

/* Linked List */
class LinkedList : public Iterable<int> {
public:
    int data;
    LinkedList* next;

    LinkedList(int val) : data(val), next(nullptr) {}

    Iterator<int>* getIterator() override;
};

/* Linked List Iterator */
class LinkedListIterator : public Iterator<int> {
    LinkedList* curr;

public:
    LinkedListIterator(LinkedList* head) : curr(head) {}

    bool hasNext() override {
        return curr != nullptr;
    }

    int next() override {
        int val = curr->data;
        curr = curr->next;
        return val;
    }
};

/* Binary Tree */
class BinaryTree : public Iterable<int> {
public:
    int data;
    BinaryTree* left;
    BinaryTree* right;

    BinaryTree(int val) : data(val), left(nullptr), right(nullptr) {}

    Iterator<int>* getIterator() override;
};

/* Binary Tree Inorder Iterator */
class BinaryTreeIterator : public Iterator<int> {
    stack<BinaryTree*> st;

    void pushLeft(BinaryTree* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }

public:
    BinaryTreeIterator(BinaryTree* root) {
        pushLeft(root);
    }

    bool hasNext() override {
        return !st.empty();
    }

    int next() override {
        BinaryTree* node = st.top();
        st.pop();
        int val = node->data;
        pushLeft(node->right);
        return val;
    }
};

/* Factory methods */
Iterator<int>* LinkedList::getIterator() {
    return new LinkedListIterator(this);
}

Iterator<int>* BinaryTree::getIterator() {
    return new BinaryTreeIterator(this);
}

/* Demo */
int main() {
    LinkedList* head = new LinkedList(1);
    head->next = new LinkedList(2);
    head->next->next = new LinkedList(3);

    Iterator<int>* it = head->getIterator();
    while (it->hasNext()) {
        cout << it->next() << " ";
    }
    cout << endl;

    BinaryTree* root = new BinaryTree(2);
    root->left = new BinaryTree(1);
    root->right = new BinaryTree(3);

    Iterator<int>* bit = root->getIterator();
    while (bit->hasNext()) {
        cout << bit->next() << " ";
    }
}
