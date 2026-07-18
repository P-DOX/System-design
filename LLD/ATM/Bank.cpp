#include <bits/stdc++.h>
using namespace std;

class BankAccount {
    public:
        string id;
        int balance;
        BankAccount(string id, int balance) : id(id), balance(balance) {}

        int getAvailablebalance() {
            return balance;
        }

        void deductBalance(int amount) {
            if(amount > this->balance)
                return;
            this->balance -= amount;
            cout<<"Available balance : "<<getAvailablebalance()<<endl;
        }
};

class ATMCard {
    public:
        string id;
        string pin;
        string bank_id;
        ATMCard(string id, string pin) : id(id), pin(pin), bank_id("BankID0") {}
};

class Userprofile {
    public:
        string id;
        string name;
        BankAccount* account;
        ATMCard* card;

        Userprofile(string id, string name, ATMCard* card) {
            account = new BankAccount("BA" + id, 20000);
            this->id = id;
            this->name = name;
            this->card = card;
        }

        BankAccount* getBankAccount() {
            return account;
        }
};

class Bank {
    public:
        string id;
        string name;
        vector<Userprofile*> userList;
        map<string, Userprofile*> cardToUser;

        Bank(string id, string name) {
            this->id = id;
            this->name = name;

            ATMCard* c1 = new ATMCard("123", "123");
            ATMCard* c2 = new ATMCard("234", "234");
            ATMCard* c3 = new ATMCard("345", "345");

            Userprofile* p1 = new Userprofile("1", "Amit", c1);
            Userprofile* p2 = new Userprofile("2", "Aman", c2);
            Userprofile* p3 = new Userprofile("3", "Rahul", c3);
            this->userList = {p1, p2, p3};
            
            this->cardToUser["123"] = p1;
            this->cardToUser["234"] = p2;
            this->cardToUser["345"] = p3;
        }

        Userprofile* getUserForCardID(string cid, string pin) {
            auto it = cardToUser.find(cid);
            if(it == cardToUser.end())
                return nullptr;
            Userprofile* up = it->second;
            if(up->card->pin == pin)
                return up;
            return nullptr;
        }

};

class CardService {
    public:
        map<string, Bank*> banks;
        CardService() {
            Bank* b = new Bank("BankID0", "BankName0");
            this->banks["BankID0"] = b;
        }

        Userprofile* getUserProfile(string cid, string pin, string bankId) {
            return banks[bankId]->getUserForCardID(cid, pin);
        }
};
