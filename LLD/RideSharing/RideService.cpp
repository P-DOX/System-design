#include <bits/stdc++.h>
#include "DriverManagementService.cpp"
using namespace std;

int IDcount = 0;

class RideState;
class Ride {
    public:
        string id;
        User* user;
        Location* pickup;
        Location* drop;
        Driver* driver;
        RideState* state;
        Ride(User* user, Location* pickup, Location* drop, Driver* driver);
        void startRide();
        void endRide();
        double getDistance();
        int getAmount();
};

class RideState {
    public:
        virtual void startRide(Ride* ride) = 0;
        virtual void endRide(Ride* ride) = 0;
        virtual string getState() = 0;
};

class RideStateCompleted : public RideState {
    public:
        void startRide(Ride* ride) override {
            cout<<"Ride completed already\n";
        }

        void endRide(Ride* ride) override {
            cout<<"Ride completed already\n";
        }

        string getState() override {
            return "COMPLETED";
        }
};

class RideStateStarted : public RideState {
    public:
        void startRide(Ride* ride) override {
            cout<<"Ride already started!\n";
        }

        void endRide(Ride* ride) override {
            ride->state = new RideStateCompleted();
        }

        string getState() override {
            return "STARTED";
        }
};

class RideStateRequested : public RideState {
    public:
        void startRide(Ride* ride) override {
            ride->state = new RideStateStarted();
        }

        void endRide(Ride* ride) override {
            ride->state = new RideStateCompleted();
        }

        string getState() override {
            return "REQUESTED";
        }
};

Ride::Ride(User* user, Location* pickup, Location* drop, Driver* driver) {
    state = new RideStateRequested();
    this->user = user;
    this->pickup = pickup;
    this->drop = drop;
    this->driver = driver;
    this->id = "RideID" + to_string(IDcount++);
}

void Ride::startRide() {
    cout<<"Start ride request received currState< "<<state->getState()<<" >"<<endl;
    state->startRide(this);
    cout<<"Start ride request fullfilled currState< "<<state->getState()<<" >"<<endl;
}

void Ride::endRide() {
    cout<<"End ride request received currState< "<<state->getState()<<" >"<<endl;
    state->endRide(this);
    cout<<"End ride request fullfilled currState< "<<state->getState()<<" >"<<endl;
}

double Ride::getDistance() {
    return sqrt(pow(this->drop->lati - this->pickup->lati, 2) + pow(this->drop->longi - this->pickup->longi, 2));
}

int Ride::getAmount() {
    int dist = getDistance();
    int amount = dist * 5;
    cout<<"Distance : "<<dist<<" Amount : $"<<amount<<endl;
    return amount;
}

class RideManagementService {
    public:
        map<string, Ride*> rideToId;
        DriverManagementService* driverService;

        RideManagementService() {
            driverService = new DriverManagementService();
        }

        Ride* getRideByID(string id) {
            return rideToId[id];
        }

        void startRideById(string id) {
            getRideByID(id)->startRide();
        }

        void endRideById(string id) {
            getRideByID(id)->endRide();
        }

        string RequestNewRide(User* user, Location* pickup, Location* drop) {
            Driver* d = driverService->findNearestDriverToLocation(pickup);
            Ride* r = new Ride(user, pickup, drop, d);
            rideToId[r->id] = r;
            cout<<"New Ride "<<r->id<<" created!!\n";
            return r->id;
        }

        int getAmountForRide(string id) {
            return getRideByID(id)->getAmount();
        }
};

class PaymentStrategy {
    public:
        virtual void pay(int amount) =0;
};

class PaymentStrategyUPI : public PaymentStrategy {
    public:
        void pay(int amount) override{
            cout<<"Amount $"<<amount<<" paid by UPI\n";
        }
};

class PaymentStrategyCard : public PaymentStrategy {
    public:
        void pay(int amount) override{
            cout<<"Amount $"<<amount<<" paid by Card\n";
        }
};

class PaymentProcessor {
    public:
        PaymentStrategy* strategy;

        void pay(int amount) {
            int choice;
            cout<<"1. UPI\n2. Card\n";
            cin>>choice;
            while(true){
                if(choice == 1) {
                    strategy = new PaymentStrategyUPI();
                    break;
                }
                else if(choice == 2) {
                    strategy = new PaymentStrategyCard();
                    break;
                }
                else{
                    cout<<"Retry\n";
                    cin>>choice;
                }
            }

            strategy->pay(amount);
        }
};

class RideBookingService {
    public:
        PaymentProcessor* paymentService;
        RideManagementService* rideService;

        RideBookingService() {
            paymentService = new PaymentProcessor();
            rideService = new RideManagementService();
        }

        string bookRide(User* user, Location* pickup, Location* drop) {
            return rideService->RequestNewRide(user, pickup, drop);
        }

        void startRide(string id) {
            rideService->startRideById(id);
        }

        void endRide(string id) {
            rideService->endRideById(id);
        }

        void payForRide(string id) {
            int amount = rideService->getAmountForRide(id);
            paymentService->pay(amount);
        }
};
