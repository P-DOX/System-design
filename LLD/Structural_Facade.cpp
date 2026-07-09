#include <bits/stdc++.h>
using namespace std;

class TV {
    public:
        void display(bool power){
            cout<<"TV is "<<(power ? "ON" : "OFF")<<endl;
        }    
};

class Sound {
    public:
        void SetVolume(int vol) {
            cout<<"Volume is "<<vol<<endl;
        }
};

class Brightness {
    public:
        void SetBrightness(int val) {
            cout<<"Brightness is "<<val<<endl;
        }
};

class HomeTheatreFacade {
    TV* tv_;
    Sound* sound_;
    Brightness* brightness_;

    public:
        HomeTheatreFacade() {
            tv_ = new TV();
            sound_ = new Sound();
            brightness_ = new Brightness();
        }

        void Start() {
            tv_->display(true);
            sound_->SetVolume(47);
            brightness_->SetBrightness(79);
        }

        void Stop() {
            tv_->display(false);
            sound_->SetVolume(0);
            brightness_->SetBrightness(0);
        }
};

int main() {
    HomeTheatreFacade* ht = new HomeTheatreFacade();
    ht->Start();
    ht->Stop();
}