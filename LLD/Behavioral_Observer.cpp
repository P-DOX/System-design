#include <bits/stdc++.h>
using namespace std;

class Observer {
    public: 
        virtual void update(int temp) = 0;
};

class PhoneDisplay : public Observer {
    public:
        void update(int temp) override {
            cout<<"Phone display temp is updated to "<<temp<<endl;
        }
};

class PCDisplay : public Observer {
    public:
        void update(int temp) override {
            cout<<"PC display temp is updated to "<<temp<<endl;
        }
};

class Observable {
    public:
        vector<Observer*> observers;
        virtual void notify(int val) = 0;
        virtual void addObserver(Observer* ob) = 0;
        virtual void removeObserver(Observer* ob) = 0;
};

class Weather : public Observable{
    public:
        int temp;
        Weather(int temp) : temp(temp) {}
        
        void addObserver(Observer* ob) override{
            observers.push_back(ob);
        }

        void removeObserver(Observer* ob) override {
            erase(observers, ob);
        }

        void notify(int temp) override {
            for(auto ob : observers) {
                ob->update(temp);
            }
        }

        void setTemperature(int temp) {
            this->temp = temp;
            notify(temp);
        }
};


int main() {
    PhoneDisplay* pd = new PhoneDisplay();
    PCDisplay* pcd = new PCDisplay();

    Weather* we = new Weather(23);
    we->addObserver(pd);
    we->addObserver(pcd);

    we->setTemperature(34);

    we->removeObserver(pcd);
    we->setTemperature(47);
}