#ifndef RESTRAUNT_MANAGER_H
#define RESTRAUNT_MANAGER_H

#include <bits/stdc++.h>
#include "../models/Restraunt.h"
using namespace std;

class RestrauntManager{
    private:
    vector<Restraunt> restaurants;
    static RestrauntManager* instance;
    RestrauntManager() {}
    public:
    static RestrauntManager* getInstance(){
        if(!instance){
            instance=new RestrauntManager();
        }
        return instance;
    }
    void addRestaurant(const Restraunt& r){
        restaurants.push_back(r);
    }
    vector<Restraunt> getRestaurants(){
        return restaurants;
    }
    vector<Restraunt> searchByLocation(const string& loc){
        vector<Restraunt> result;
        for(auto& r:restaurants){
            if(r.getLocation()==loc){
                result.push_back(r);
            }
        }
        return result;
    }
};

RestrauntManager* RestrauntManager::instance=nullptr;

#endif // RESTRAUNT_MANAGER_H