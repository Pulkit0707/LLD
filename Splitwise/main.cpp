#include <bits/stdc++.h>
using namespace std;

class User{
    public:
    string id;
    string name;
    unordered_map<string,int>balance;
};

class Group{
    string id;
    string name;
public:
    vector<User> members;
    unordered_map<string,int>balance;
    void addUser(User user){
        members.push_back(user);
        balance[user.id] = 0;
    }
    bool removeUser(User user){
        for(int i=0;i<members.size();i++){
            if(members[i].id == user.id){
                if(balance[user.id] != 0){
                    cout<<"User has non-zero balance, cannot remove"<<endl;
                    return false;
                }
                members.erase(members.begin()+i);
                balance.erase(user.id);
                return true;
            }
        }
        return false;
    }
    void addExpense(User* user,int amount){
        balance[user->id] += amount;
        cout<<"User "<<user->name<<" added "<<amount<<" in group "<<name<<endl;
        
    }
    void settleExpense(User* user,int amount){
        balance[user->id] -= amount;
        cout<<"User "<<user->name<<" settled "<<amount<<" in group "<<name<<endl;
    }
};

class Expense{
    string id;
    string desc;
    ExpenseStrategy* strategy;
    public:
    Group* group;
    Expense(string id,string desc,ExpenseStrategy* strategy,Group* group){
        this->id = id;
        this->desc = desc;
        this->strategy = strategy;
        this->group = group;
    }
    void divideExpense(){
        unordered_map<User*,int> expenseMap = strategy->calculateExpense(*this);
        for(auto it: expenseMap){
            group->addExpense(it.first,it.second);
        }
    }
};

class ExpenseStrategy{
    public:
    virtual unordered_map<User*,int> calculateExpense(Expense* expense) = 0;
};

class EqualExpenseStrategy: public ExpenseStrategy{
    int totalAmount;
    public:
    EqualExpenseStrategy(int totalAmount){
        this->totalAmount = totalAmount;
    }
    unordered_map<User*,int> calculateExpense(Expense* expense) override{
        unordered_map<User*,int> result;
        int numUsers = expense->group->members.size();
        int amountPerUser = totalAmount / numUsers;
        for(User user: expense->group->members){
            result[&user] = amountPerUser;
        }
        return result;
    };
};

class ExactExpenseStrategy: public ExpenseStrategy{
    unordered_map<User*,int> exactAmounts;
    public:
    ExactExpenseStrategy(unordered_map<User*,int> exactAmounts){
        this->exactAmounts = exactAmounts;
    }
    unordered_map<User*,int> calculateExpense(Expense* expense) override{
        return exactAmounts;
    };
};

class PercentExpenseStrategy: public ExpenseStrategy{
    unordered_map<User*,int> percentAmounts;
    int totalAmount;
    public:
    PercentExpenseStrategy(int totalAmount,unordered_map<User*,int> percentAmounts){
        this->totalAmount = totalAmount;
        this->percentAmounts = percentAmounts;
    }
    unordered_map<User*,int> calculateExpense(Expense* expense) override{
        unordered_map<User*,int> result;
        for(auto it: percentAmounts){
            result[it.first] = (totalAmount * it.second) / 100;
        }
        return result;
    };
};

int main(){

}