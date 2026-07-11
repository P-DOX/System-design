#include <bits/stdc++.h>
using namespace std;

class State {
    public:
        virtual void handleState() = 0;
};

enum ReviewState {STARTED, PENDING, APPROVED};

class StartedState : public State {
    public:
        void handleState() override {
            cout<<"Handling STARTED state\n";
        }
};

class PendingState : public State {
    public:
        void handleState() override {
            cout<<"Handling PENDING state\n";
        }
};

class ApprovedState : public State {
    public:
        void handleState() override {
            cout<<"Handling APPROVED state\n";
        }
};

class DocumentReview {
    private:
        State* currentState;
    public:
        DocumentReview(State* state) : currentState(state) {}
        
        void processCurrentState() {
            currentState->handleState();
        }

        void setState(State* s) {
            currentState = s;
        }
};

int main() {
    State* s1 = new StartedState();
    State* s2 = new PendingState();
    State* s3 = new ApprovedState();

    DocumentReview* d = new DocumentReview(s1);
    d->processCurrentState();
    
    d->setState(s2);
    d->processCurrentState();

    d->setState(s3);
    d->processCurrentState();
}