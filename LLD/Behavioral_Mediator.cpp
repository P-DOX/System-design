#include <bits/stdc++.h>
using namespace std;

class Aeroplane;

class Mediator {
    public:
        virtual void notify(Aeroplane* sender, string msg) = 0;
        virtual void registerAeroplanes(Aeroplane* a) = 0;
};

class Aeroplane {
    public: 
        string name;
        Mediator* mt;
        Aeroplane(string name, Mediator* mt) : name(name), mt(mt) {
            mt->registerAeroplanes(this);
        }

        void requestLanding() {
            mt->notify(this, " Landing requested!\n");
        }

        void requestTakeoff() {
            mt->notify(this, " Takeoff requested!\n");
        }

        void receiveMSG(string msg) {
            cout<<name + " <MESSAGE ATC> "<<msg<<endl;
        }
};

class ATCMediator : public Mediator {
    public:
        vector<Aeroplane*> lst;
        void registerAeroplanes(Aeroplane* a) override{
            lst.push_back(a);
        }
        void notify(Aeroplane* sender, string msg) override {
            cout<<"MESSAGE RECEIVED from "<<sender->name<<" "<<msg<<endl;
            for(auto l : lst) {
                if(l != sender)
                    l->receiveMSG("ALERT\n");
            }
        }
};

int main() {
    ATCMediator* atc = new ATCMediator();
    Aeroplane* a1 = new Aeroplane("F1", atc);
    Aeroplane* a2 = new Aeroplane("F2", atc);
    Aeroplane* a3 = new Aeroplane("F3", atc);
    
    a1->requestLanding();

}