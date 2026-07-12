#include <bits/stdc++.h>
#include "Product.cpp"


using namespace std;



int main() {
    Shop* s = new Shop(1, "Gaurav Kirana store");
    s->printEverything();
    Product* p = s->getProducts()[0];
    s->buyProduct(p, 5);
    s->refillProduct(p, 45);
}