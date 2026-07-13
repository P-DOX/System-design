#include <bits/stdc++.h>
using namespace std;

class Product {
    public:
        int id;
        string name;
        int price;
        int ph_qty;
        int rsvd_qty;
        Product(int id, string name, int price, int ph_qty, int rsvd_qty) : id(id), name(name), price(price), ph_qty(ph_qty), rsvd_qty(rsvd_qty) {}
};

class InventoryService {
    public:
        map<int, Product*> productById;
        InventoryService() {
            Product* p1 = new Product(1, "Salt", 20, 10, 0);
            productById[1] = p1;
            Product* p2 = new Product(2, "Sugar", 30, 10, 0);
            productById[2] = p2;
            Product* p3 = new Product(3, "Cover", 40, 10, 0);
            productById[3] = p3;
            Product* p4 = new Product(4, "Tea", 50, 10, 0);
            productById[4] = p4;
            Product* p5 = new Product(5, "Snacks", 60, 10, 0);
            productById[5] = p5;
        }

        vector<Product*> getProductList() {
            vector<Product*> v;
            for(auto it = productById.begin(); it!=productById.end(); it++){
                v.push_back(it->second);
            }
            return v;
        }

        bool reserveProduct(int id, int q) {
            auto it = productById.find(id);
            if(it == productById.end() or (it->second->ph_qty - it->second->rsvd_qty) < q) {
                cout<<"Product "<<id<<" Not Available\n";
                return false;
            }

            it->second->rsvd_qty += q;
            cout<<"Product "<<id<<" Qty : "<<q<<" reserved\n";
            return true;
        }

        void revertReserve(int id, int q) {
            auto it = productById.find(id);
            it->second->rsvd_qty -= q;
            cout<<"Product "<<id<<" Qty : "<<q<<" reserve reverted\n";
        }

        bool buyProduct(int id, int q) {
            auto it = productById.find(id);
            if(it == productById.end() or it->second->ph_qty < q) {
                cout<<"Product "<<id<<" Not Available\n";
                return false;
            }

            it->second->ph_qty -= q;
            cout<<"Product "<<id<<" Qty : "<<q<<" bought\n";
            return true;
        }

        void refillProduct(int id, int q) {
            auto it = productById.find(id);
            it->second->ph_qty += q;
        }
};

class Store {
    public:
        Staff* mngr;
        InventoryService* inventory;

        Store(Staff* mngr) : mngr(mngr){
            inventory = new InventoryService();
        } 

        vector<Product*> getProductList() {
            return inventory->getProductList();
        }

        void printInventory() {
            auto v = getProductList();
            for(Product* p : v) {
                cout<<p->id<<" "<<p->name<<" ph_qty : "<<p->ph_qty<<" rsvd_qty : "<<p->rsvd_qty<<" Price : $"<<p->price<<endl;
            }
        }

        void reserveProduct(int id, int  q) {
            inventory->reserveProduct(id, q);
        }

        void revertReserveProduct(int id, int q) {
            inventory->revertReserve(id, q);
        }

        void buyProduct(int id, int q) {
            inventory->buyProduct(id, q);
        }

        void refillProduct(int id, int q) {
            inventory->refillProduct(id, q);
        }
};