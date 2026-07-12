#include <bits/stdc++.h>

using namespace std;

class Observer {
    public:
        virtual void notify(string msg) = 0;
};

class User{
    public:
        string name;
        int id;
        User(string name, int id) : name(name), id(id) {}
};

class Staff : public Observer, public User {
    public:
    Staff(int id, string name) : User(name, id) {}

    void notify(string msg) override {
        cout<<"Staff notified "<<name<<" "<<msg<<endl;
    }
};

class Customer : public Observer, public User {
    public:
    Customer(int id, string name) : User(name, id) {}

    void notify(string msg) override {
        cout<<"Customer notified "<<name<<" "<<msg<<endl;
    }
};

class Observable {
    public:
        vector<Observer*> observerList;
        void addObserver(Observer* ob) {
            observerList.push_back(ob);
        }
        
        void removeObserver(Observer* ob) {
            erase(observerList, ob);
        }
        
        void notify(string msg) {
            for(auto ob : observerList) {
                ob->notify(msg);
            }
        }
};