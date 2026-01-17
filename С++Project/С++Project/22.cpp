#include<iostream>
#include<string>
#include <vector>
using namespace std;

class Weapon {                   
public:
	int demage = 60;              //Зброя
	float cooldown = 1.5;
	std::string icon;
};


class Enemy {
public:
	int HealthEnemy = 50;
	void TakeDemage(int demage) {                            //Ворог
		HealthEnemy -= demage;
		if (HealthEnemy <= 0) { HealthEnemy = 0; }
	} 
};


class Character{                   //персонаж
	
	public: string name;
	int health=40;
	int IQ=7;
	int agility=5;

	Weapon weapon;
	void Attack(Enemy& target) {
		target.TakeDemage(weapon.demage);

		cout << name << " attacks Enemy with " << weapon.demage << " demage!" << endl;
		cout << "Enemy health now: " << target.HealthEnemy << endl;
	}
};


	class PasiveItem {                                   //Амулети
    public:
	int BonusHealth = 15;                                  
	int BonusIQ = 10;
	int BonusAgility = 4;

	void apply(Character& Character) {
		Character.health += BonusHealth;
		Character.IQ += BonusIQ;
		Character.agility += BonusAgility;
	}
};


	
		


	int main() {
		Character hero;
		cout << "Set Hero name: ";
		cin >> hero.name;
		cout << "Hero health is: " << hero.health <<", IQ: "<<hero.IQ<<", Agility: "<<hero.agility<<endl;

		PasiveItem amulet;
		amulet.apply(hero);
		cout << "Amulet changed abilities:" << endl;
		cout << "Health: " << hero.health << ", IQ: " << hero.IQ << ", Agility: " << hero.agility << endl;

		Enemy enemy;
		hero.Attack(enemy); // Тепер герой атакує ворога
		if (enemy.HealthEnemy == 0) {
			cout << "Enemy is dead";}
		return 0;
	}