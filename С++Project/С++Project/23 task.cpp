#include<iostream>
#include<string>
#include<vector>
#include <memory>
using namespace std;

class Character {
public: string name;
        int health;
        int speed;
        int power;
    
    Character(): health(100), speed(30), power(20){}
    
   
     };

class Weapon {
    public:string name;
    int weaponPower = 26;
    void EquipWeapon(Character& target) {
        target.power += weaponPower;
        if (target.power > 100) target.power = 100;
    }
};

class Amulet {
public: int speedValue;

      Amulet() : speedValue(30) {};
      void Addspeed(Character& target) {
          target.speed += speedValue;
          if (target.speed > 100) target.speed = 100;
      }

};



int main()
{
    auto Player = make_unique<Character> ();
    auto Item = make_unique<Amulet>();
    auto Sword = make_unique<Weapon>();
    cout << "Write name: ";
    cin >> Player->name;
    cout << "Speed is: " << Player->speed << endl;
    Item->Addspeed(*Player);
    cout << "Speed after using item is:" << Player->speed << endl;
    cout << "Power is: "<< Player->power<< endl;
    
    Sword->EquipWeapon(*Player);

    cout << "Power after equip sword is:" << Player->power << endl;


    
   
    
  
    

    
    
   






    return 0;
}