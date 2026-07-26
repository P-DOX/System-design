#include <bits/stdc++.h>
using namespace std;

class Location {
    public:
        double lati;
        double longi;
        Location(double lati, double longi) : lati(lati), longi(longi) {}
};

class Driver {
    public:
        string id;
        string name;
        Location* currLoc;

        Driver(string id, string name, Location* loc) : id(id), name(name), currLoc(loc) {}
};

class User {
    public:
        string id;
        string name;
        Location* currLoc;

        User(string id, string name, Location* loc) : id(id), name(name), currLoc(loc) {}
};

class DriverFindingStrategy {
    public:
        virtual Driver* findDriver(vector<Driver*> lst) = 0;
};

class DriverFindingStrategyByDistance : public DriverFindingStrategy {
    public:
        Driver* findDriver(vector<Driver*> lst) override {
            cout<<"Finding nearest driver by distance strategy\n";
            return lst[0]; //test
        }
};

class DriverFindingStrategyByTime : public DriverFindingStrategy {
    public:
        Driver* findDriver(vector<Driver*> lst) override {
            cout<<"Finding nearest driver by time strategy\n";
            return lst[lst.size()-1]; //test
        }
};

class DriverManagementService {
    public:
        vector<Driver*> lst;
        DriverFindingStrategy* strategy;
        
        DriverManagementService() {
            Location* l1 = new Location(12.23, 45.56);
            Location* l2 = new Location(4567.23, 132.56);
            Location* l3 = new Location(7543.23, 354.56);
            Driver* d1 = new Driver("d1", "dname1", l1);
            Driver* d2 = new Driver("d2", "dname2", l2);
            Driver* d3 = new Driver("d3", "dname3", l3);
            lst = {d1, d2, d3};
            strategy = new DriverFindingStrategyByDistance();
        }
        
        Driver* findNearestDriverToLocation(Location* loc) {
            return strategy->findDriver(lst);
        }
};