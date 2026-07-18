#include <bits/stdc++.h>
#include "Bank.cpp"
using namespace std;

class ATMCurrentState {
    public:
        virtual void idleScreen() {cout<<"Not supposed to enter in ATMCurrentState_Idle\n";}
        virtual void authenticate() {cout<<"Not supposed to enter in ATMCurrentState_CardInsert\n";}
        virtual void getMenu() {cout<<"Not supposed to enter in ATMCurrentState_Menu\n";}
        virtual void checkBalance() {cout<<"Not supposed to enter in ATMCurrentState_CheckBalance\n";}
        virtual void showFailure(string msg) {cout<<"Not supposed to enter in ATMCurrentState_Failure\n";}
        virtual void executeWithdrawal(int amount) {cout<<"Not supposed to enter in ATMCurrentState_WithdrawMoney\n";}
};

class ATM {
    public:
        string id;
        CardService* cs;
        ATMCurrentState* state;

        ATM(string id);

        void insertCard(ATMCard* card);
};
// enum ATMStates {
//     ATMCurrentState_Idle,
//     ATMCurrentState_CardInsert,
//     ATMCurrentState_Menu,
//     ATMCurrentState_CheckBalance,
//     ATMCurrentState_WithdrawMoney,
//     ATMCurrentState_Failure
// };

class ATMCurrentState_Idle : public ATMCurrentState {
    public:
        ATM* atm;
        ATMCurrentState_Idle(ATM* atm) : atm(atm) {}

        void idleScreen() override {
            cout<<"Welcome to ATM "<<atm->id<<endl;
        }
};

class ATMCurrentState_Failure : public ATMCurrentState {
    public:
        ATM* atm;
        ATMCurrentState_Failure(ATM* atm) : atm(atm) {}

        void showFailure(string msg) override {
            cout<<"Failure state msg : "<<msg;
        }
};

class ATMCurrentState_CheckBalance : public ATMCurrentState {
    public:
        ATM* atm;
        Userprofile* profile;
        ATMCurrentState_CheckBalance(ATM* atm, Userprofile* profile) : atm(atm), profile(profile) {}

        void checkBalance() override {
            cout<<"Currrent balance is : "<<profile->account->getAvailablebalance()<<endl;
            this->atm->state = new ATMCurrentState_Idle(atm);
            this->atm->state->idleScreen();
        }
};

class ATMCurrentState_WithdrawMoney : public ATMCurrentState {
    public:
        ATM* atm;
        Userprofile* profile;
        ATMCurrentState_WithdrawMoney(ATM* atm, Userprofile* profile) : atm(atm), profile(profile) {}

        void executeWithdrawal(int amount) override {
            profile->account->deductBalance(amount);
            this->atm->state = new ATMCurrentState_Idle(atm);
            this->atm->state->idleScreen();
        }
};

class ATMCurrentState_Menu : public ATMCurrentState {
    public:
        ATM* atm;
        Userprofile* profile;
        ATMCurrentState_Menu(ATM* atm, Userprofile* profile) : atm(atm), profile(profile) {}

        void getMenu() override {
            int choice;
            cout<<"Enter 1. Balance 2. Withdrawl\n";
            cin>>choice;

            if(choice == 1) {
                atm->state = new ATMCurrentState_CheckBalance(atm, profile);
                atm->state->checkBalance();
            }
            else if(choice == 2) {
                int amount;
                cout<<"Enter amount : ";
                cin>>amount;
                atm->state = new ATMCurrentState_WithdrawMoney(atm, profile);
                atm->state->executeWithdrawal(amount);
            }
            else {
                atm->state = new ATMCurrentState_Failure(atm);
                atm->state->showFailure("Menu failed !!\n");
            }
        }
};




class ATMCurrentState_CardInsert : public ATMCurrentState {
    public:
        ATM* atm;
        ATMCard* card;
        ATMCurrentState_CardInsert(ATM* atm, ATMCard* card) : atm(atm), card(card) {
            authenticate();
        }

        void authenticate() override {
            Userprofile* profile = atm->cs->getUserProfile(card->id, card->pin, card->bank_id);
            if(profile != nullptr) {
                atm->state = new ATMCurrentState_Menu(atm, profile);
                atm->state->getMenu();
            }
            else {
                atm->state = new ATMCurrentState_Failure(atm);
                atm->state->showFailure("Authentication failed!!\n");
            }
        }
};


ATM::ATM(string id) {
    this->id = id;
    this->cs = new CardService();
    this->state = new  ATMCurrentState_Idle(this);
    this->state->idleScreen();
}

void ATM::insertCard(ATMCard* card) {
    this->state = new ATMCurrentState_CardInsert(this, card);
}

int main() {
    ATM* atm = new ATM("ATMID1");
    ATMCard* card = new ATMCard("123", "123");
    atm->insertCard(card);
}