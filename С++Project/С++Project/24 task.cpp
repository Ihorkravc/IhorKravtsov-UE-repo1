#include<iostream>
#include<string>
using namespace std;
class HUD {
public:
    void Onhealthchanged(int health) {
        cout << "Resive healtH" << health << endl;
    }
};
class Hero {
public:
    int health;
    int demage;
    Hero() : health(100), demage(0) {}
    HUD* hud = nullptr;
public:
    void  setHUD(HUD* h)
    {
        hud = h;
    }
    void TakenDemage(int dmg) {
        health -= dmg;
        if (hud) {
            hud->Onhealthchanged(health);
        }
    }
};




int main()
{
    Hero hero;
    HUD hud;
    hero.setHUD(&hud);

    hero.TakenDemage(35);






    return (0);
}