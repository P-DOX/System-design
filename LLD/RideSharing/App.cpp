#include <bits/stdc++.h>
#include "RideService.cpp"
using namespace std;

class App {
    public:
    User* user;
    RideBookingService* rideService;

    App(User* user) {
        this->user = user;
        rideService = new RideBookingService();
    }

    string bookRide(Location* pickup, Location* drop) {
        return rideService->bookRide(user, pickup, drop);
    }

    void startRide(string id) {
        rideService->startRide(id);
    }

    void endRide(string id) {
        rideService->endRide(id);
    }

    void payForRide(string id) {
        rideService->payForRide(id);
    }
};


int main() {
    Location* l1 = new Location(11.23, 4.56);
    Location* l2 = new Location(341.23, 674.56);
    User* u = new User("u1", "Gaurav", l1);
    App* app = new App(u);

    string id = app->bookRide(l1, l2);
    app->startRide(id);
    app->endRide(id);
    app->startRide(id);
    app->payForRide(id);
}