#include <bits/stdc++.h>

using namespace std;

class Vehicle {
    public:    
    virtual void drive() = 0;
};

class Car : public Vehicle {
    public:
        void drive() override {
            cout<<"Car driving \n";
        }
};

class Bike : public Vehicle {
    public:
        void drive() override {
            cout<<"Bike driving\n";
        }
};

class VehicleFactory {
    public:
    Vehicle* CreateVehicle(string vehicle) {
        if(vehicle == "Bike")
            return new Bike();
        else if(vehicle == "Car")
            return new Car();
        else
            return NULL;
    }
};

int main() {
    VehicleFactory* factory = new VehicleFactory();
    Vehicle* car = factory->CreateVehicle("Car");
    Vehicle* bike = factory->CreateVehicle("Bike");
    car->drive();
    bike->drive();
    delete car;
    delete bike;
}