#include <bits/stdc++.h>
using namespace std;

class Floor;
class Elevator;

class Observer {
public:
    virtual void updateOnFloorReached(string msg) = 0;
    virtual void updateOnAlert() = 0;
};

class Observable {
public:
    vector<Observer*> obList;

    void addObserver(Observer* ob) {
        obList.push_back(ob);
    }

    void removeObserver(Observer* ob) {
        std::erase(obList, ob);
    }

    virtual void notifyFloorReached() = 0;
    virtual void notifyOnAlert() = 0;
};

class Floor {
public:
    int level;
    class ElevatorRequestPanel* rp;
    Floor(int level, class ElevatorServiceMediator* mediator);
    void requestUp();
    void requestDown();
};

class Elevator : public Observable {
public:
    int id;
    Floor* currFloor;
    Floor* currDest;
    bool dirUpToDown;
    vector<Floor*> destList;

    Elevator(int id) {
        this->id = id;
        this->currFloor = nullptr;
        this->currDest = nullptr;
        this->dirUpToDown = true;
        this->destList = {};
    }

    void moveToDir();
    void move();
    void notifyFloorReached() override;
    void notifyOnAlert() override {}
};

class ElevatorSelectionToServerRequestStrategy {
public:
    virtual Elevator* selectElevatorToServeRequest(vector<Elevator*> lst, Floor* requestFloor) = 0;
};

class ElevatorSelectionToServerRequestStrategyFirst : public ElevatorSelectionToServerRequestStrategy {
public:
    Elevator* selectElevatorToServeRequest(vector<Elevator*> lst, Floor* requestFloor) override {
        return lst[0];
    }
};

class ElevatorServiceMediator : public Observer {
public:
    int noOfElevator;
    vector<Elevator*> listOfElevator;
    ElevatorSelectionToServerRequestStrategy* strategy;

    ElevatorServiceMediator(int noOfElevator, ElevatorSelectionToServerRequestStrategy* strategy) {
        this->noOfElevator = noOfElevator;
        this->strategy = strategy;
        for(int i = 0; i < noOfElevator; i++){
            Elevator* el = new Elevator(i);
            el->addObserver(this); 
            this->listOfElevator.push_back(el);
        }
    }

    void initElevator(Floor* floor) {
        for(auto el : listOfElevator) {
            el->currFloor = floor;
            el->currDest = floor;
            el->destList = {};
        }
    }

    void sendElevatorToFloor(Elevator* el, Floor* destFloor) {
        el->currDest = destFloor;
        el->move();
        el->moveToDir(); 
    }

    void requestUp(Floor* req_floor) {
        Elevator* el = strategy->selectElevatorToServeRequest(listOfElevator, req_floor);
        sendElevatorToFloor(el, req_floor);
    }

    void requestDown(Floor* req_floor) {
        Elevator* el = strategy->selectElevatorToServeRequest(listOfElevator, req_floor);
        sendElevatorToFloor(el, req_floor);
    }

    void updateOnFloorReached(string msg) override {
        cout << "Mediator Log -> " << msg << endl;
    }

    Elevator* getElevatorByInd(int ind) {
        return listOfElevator[ind];
    }
    void updateOnAlert() override {}
};

class ElevatorRequestPanel {
public:
    ElevatorServiceMediator* mediator;
    ElevatorRequestPanel(ElevatorServiceMediator* mediator) : mediator(mediator) {}

    void requestUp(Floor* floor) {
        mediator->requestUp(floor);
    }

    void requestDown(Floor* floor) {
        mediator->requestDown(floor);
    }
};

Floor::Floor(int level, ElevatorServiceMediator* mediator) {
    this->level = level;
    rp = new ElevatorRequestPanel(mediator);
}

void Floor::requestUp() { rp->requestUp(this); }
void Floor::requestDown() { rp->requestDown(this); }

void Elevator::moveToDir() {
    if (currFloor == nullptr || currDest == nullptr) return;
    
    if (dirUpToDown) {
        cout << "[Elevator " << id << "] Moving Down from Floor " << currFloor->level << " to " << currDest->level << endl;
    } else {
        cout << "[Elevator " << id << "] Moving Up from Floor " << currFloor->level << " to " << currDest->level << endl;
    }
    currFloor = currDest; 
    notifyFloorReached();
}

void Elevator::move() {
    if (currFloor == nullptr || currDest == nullptr) return;
    
    if (currDest->level > currFloor->level) {
        dirUpToDown = false;
    } else if (currDest->level < currFloor->level) {
        dirUpToDown = true;
    } else {
        cout << "[Elevator " << id << "] Already at target floor. NO MOVE\n";
    }
}

void Elevator::notifyFloorReached() {
    for (auto ob : obList) {
        string msg = "Elevator " + to_string(id) + " safely reached Floor " + to_string(currFloor->level);
        ob->updateOnFloorReached(msg);
    }
}

class Building {
public:
    int numOfFloor;
    vector<Floor*> floors;
    ElevatorServiceMediator* mediator;

    Building(int numOfFloor, ElevatorServiceMediator* mediator) {
        this->numOfFloor = numOfFloor;
        this->mediator = mediator;
        for(int level = 1; level <= numOfFloor; level++){
            floors.push_back(new Floor(level, mediator));
        }
    }

    Elevator* getElevator(int ind) {
        return mediator->getElevatorByInd(ind);
    }

    void requestUpFromFloor(Floor* req_floor) {
        req_floor->requestUp();
    }

    void requestDownFromFloor(Floor* req_floor) {
        req_floor->requestDown();
    }
};

int main() {
    ElevatorSelectionToServerRequestStrategy* strategy = new ElevatorSelectionToServerRequestStrategyFirst();
    ElevatorServiceMediator* mediator = new ElevatorServiceMediator(3, strategy);
    Building* b = new Building(10, mediator);
    
    mediator->initElevator(b->floors[0]);

    cout << "--- Simulating Request from Floor 4 ---" << endl;
    b->requestUpFromFloor(b->floors[3]); 
    Elevator* el = mediator->getElevatorByInd(0);
    mediator->sendElevatorToFloor(el, b->floors[9]);

    b->requestDownFromFloor(b->floors[9]);
    b->requestDownFromFloor(b->floors[2]);
    mediator->sendElevatorToFloor(el, b->floors[6]);

    return 0;
}