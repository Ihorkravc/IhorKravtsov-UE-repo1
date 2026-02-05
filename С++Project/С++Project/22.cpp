#include <iostream>
#include <string>
using namespace std;

// ---------------- Weapon ----------------
class Weapon {
private:
    int damage = 60;
    float cooldown = 1.5f;
    string icon;

public:
    int GetDamage() const {
        return damage;
    }
};

// ---------------- PassiveItem ----------------
class PassiveItem {
private:
    int bonusHealth = 15;
    int bonusIQ = 10;
    int bonusAgility = 4;


public:
    int GetBonusHealth() const { return bonusHealth; }
    int GetBonusIQ() const { return bonusIQ; }
    int GetBonusAgility() const { return bonusAgility; }
};

// ---------------- Character ----------------
class Character {
protected:
    string name;
    int health = 40;
    int IQ = 7;
    int agility = 5;

    Weapon weapon;

public:
    void SetName(const string& newName) {
        name = newName;
    }

    int GetHealth() const {
        return health;
    }

    void ApplyPassiveItem(const PassiveItem& item) {
        health += item.GetBonusHealth();
        IQ += item.GetBonusIQ();
        agility += item.GetBonusAgility();
    };

    void TakeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    void Attack(Character& target) {
        int damage = weapon.GetDamage();
        target.TakeDamage(damage);

        cout << name << " attacks for " << damage << " damage!" << endl;
        cout << "Target health: " << target.GetHealth() << endl;
    }
};

// ---------------- Enemy ----------------
class Enemy : public Character {
public:
    Enemy() {
        health = 50;
        name = "Enemy";
    }

    bool IsDead() const {
        return health == 0;
    }
};

// ---------------- main ----------------
int main() {
    Character hero;
    cout << "Set Hero name: ";
    string heroName;
    cin >> heroName;
    hero.SetName(heroName);

    cout << "Hero health: " << hero.GetHealth() << endl;

    PassiveItem amulet;
    hero.ApplyPassiveItem(amulet);

    cout << "After amulet, hero health: " << hero.GetHealth() << endl;

    Enemy enemy;
    hero.Attack(enemy);

    if (enemy.IsDead()) {
        cout << "Enemy is dead!" << endl;
    }

    return 0;
}