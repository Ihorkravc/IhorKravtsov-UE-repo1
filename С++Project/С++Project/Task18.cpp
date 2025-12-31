#include <iostream>
#include <vector>
#include <string>
using namespace std;

// —труктура дл€ гравц€
struct Player {
    string name;  // ≥м'€ гравц€
    int health;   // здоров'€ гравц€
};

// ‘ункц≥€ дл€ зчитуванн€ к≥лькост≥ гравц≥в
int readNumberOfPlayers() {
    int n;
    cout << "Enter number of players: ";
    cin >> n;
    return n;
}

// ‘ункц≥€ дл€ зчитуванн€ даних гравц≥в
void readPlayers(vector<Player>& players, int n) {
    for (int i = 0; i < n; i++) {
        Player p;
        cout << "Enter name of player " << i + 1 << ": ";
        cin >> p.name;
        cout << "Enter health of player " << p.name << ": ";
        cin >> p.health;
        players.push_back(p);
    }
}

// ‘ункц≥€ дл€ застосуванн€ шкоди вс≥м гравц€м
void applyDamage(vector<Player>& players, int damage) {
    for (auto& p : players) {
        p.health -= damage;
    }
}

// ‘ункц≥€ дл€ пошуку гравц€ з найб≥льшим здоров'€м
Player findMaxHealth(const vector<Player>& players) {
    Player maxPlayer = players[0];
    for (const auto& p : players) {
        if (p.health > maxPlayer.health) {
            maxPlayer = p;
        }
    }
    return maxPlayer;
}

// ‘ункц≥€ дл€ пошуку гравц€ з найменшим здоров'€м
Player findMinHealth(const vector<Player>& players) {
    Player minPlayer = players[0];
    for (const auto& p : players) {
        if (p.health < minPlayer.health) {
            minPlayer = p;
        }
    }
    return minPlayer;
}

// ‘ункц≥€ дл€ виведенн€ мертвих гравц≥в
void printDeadPlayers(const vector<Player>& players) {
    bool anyDead = false;
    for (const auto& p : players) {
        if (p.health <= 0) {
            cout << p.name << " is dead." << endl;
            anyDead = true;
        }
    }
    if (!anyDead) {
        cout << "No dead players." << endl;
    }
}

int main() {
    int numPlayers = readNumberOfPlayers();  // зчитати к≥льк≥сть гравц≥в
    vector<Player> players;

    readPlayers(players, numPlayers);  // зчитати дан≥ вс≥х гравц≥в

    int damage;
    cout << "Enter damage amount: ";
    cin >> damage;

    applyDamage(players, damage);  // застосувати шкоду вс≥м гравц€м

    int query;
    cout << "Enter query option (1 - max health, 2 - min health, 3 - dead players): ";
    cin >> query;

    // ќбробка запиту
    switch (query) {
    case 1: {
        Player maxPlayer = findMaxHealth(players);
        cout << "Player with max health: " << maxPlayer.name << " (" << maxPlayer.health << ")" << endl;
        break;
    }
    case 2: {
        Player minPlayer = findMinHealth(players);
        cout << "Player with min health: " << minPlayer.name << " (" << minPlayer.health << ")" << endl;
        break;
    }
    case 3:
        printDeadPlayers(players);  // вивести мертвих гравц≥в
        break;
    default:
        cout << "Invalid query option." << endl;
    }

    return 0;
}
