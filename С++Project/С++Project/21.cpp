
#include <iostream>
#include <string>
#include <vector>
#include <limits> // для numeric_limits

using namespace std;

// структура для координат
struct Position {
    int x;
    int y;
};

// клас героя
class Hero {
public:
    string name;
    int Health = 100;
    Position position;
    int speed = 1;

public:
    void Move(int dx, int dy) {
        position.x += dx * speed;
        position.y += dy * speed;
    }
};

// глобальні змінні
int N;
vector<Hero> Heros;

int main() {
    cout << "How many players do you have? ";
    cin >> N;

    // Введення героїв
    for (int i = 0; i < N; i++) {
        Hero Myhero;
        cout << "Set name: ";
        cin >> Myhero.name;
        cout << "Set health: ";
        cin >> Myhero.Health;
        cout << "Set position x: ";
        cin >> Myhero.position.x;
        cout << "Set position y: ";
        cin >> Myhero.position.y;
        cout << "Set speed: ";
        cin >> Myhero.speed;

        Heros.push_back(Myhero);
    }

    int numCommands;
    cout << "How many moves?: ";
    cin >> numCommands;

    // очищаємо буфер перед введенням команд
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Введення команд руху
    for (int i = 0; i < numCommands; i++) {
        int HeroIndex, dx, dy;
        cout << "Command #" << i + 1 << " (heroIndex dx dy): ";
        cin >> HeroIndex >> dx >> dy;

        // перевірка індексу
        if (HeroIndex < 0 || HeroIndex >= Heros.size()) {
            cout << "Invalid hero index!" << endl;
            i--; // повторюємо цю команду
            cin.clear(); // очищаємо стан потоку
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        Heros[HeroIndex].Move(dx, dy);
    }

    // Вивід нових позицій героїв
    for (int i = 0; i < Heros.size(); i++) {
        cout << Heros[i].name << " is at ("
            << Heros[i].position.x << ", "
            << Heros[i].position.y << ")" << endl;
    }

    return 0;
}
