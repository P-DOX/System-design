#include <bits/stdc++.h>
using namespace std;

class Location {
    public:
        string pin;
        Location(string pin) : pin(pin) {}
};

enum StaffCategory {STORE_MANAGER, DELIVERY_AGENT};

class Customer {
    public:
        int id;
        string name;
        Customer(int id, string name) : id(id), name(name) {}
};

class Staff {
    public:
        int id;
        string name;
        StaffCategory cat;
        Staff(int id, string name) : id(id), name(name), cat(STORE_MANAGER) {}
};

class DeliveryAgent : public Staff {
    public:
        Location* loc;
        DeliveryAgent(int id, string name) : Staff(id, name) {
            this->loc = new Location("12345");
            this->cat = DELIVERY_AGENT;
        }
};
