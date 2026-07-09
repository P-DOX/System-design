#include <bits/stdc++.h>
using namespace std;

class Internet {
    public:
        virtual void ConnectTo(string domain) = 0;
};

class RealInternet : public Internet{
    public:
        void ConnectTo(string domain) override{
            cout<<"Real Connecting to "<<domain<<"...\n";
        }
};

class ProxyInternet : public Internet {
    private:
        RealInternet* internet;
        vector<string> banned_sites;
    
    public:
        ProxyInternet() {
            internet = new RealInternet();
            banned_sites = {"a.com", "b.com"};
        }
        
        void ConnectTo(string domain) override{
            if(find(banned_sites.begin(), banned_sites.end(), domain) == banned_sites.end()) {
                cout<<"Proxy Connecting to "<<domain<<"...\n";
                internet->ConnectTo(domain);
            }
            else {
                cout<<"Banned page..."<<domain<<"\n";
            }
        }
};

int main() {
    ProxyInternet* proxy = new ProxyInternet();
    proxy->ConnectTo("a.com");
    proxy->ConnectTo("b.com");
    proxy->ConnectTo("c.com");
}