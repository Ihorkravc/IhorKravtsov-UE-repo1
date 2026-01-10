#include <iostream>;
#include <string>;
#include <vector>;

using namespace std;

//оголошення структур
struct Position  { int x; int y; };
struct Meteor {
	int demage=70;
	int power=3;
	Position position;
};

struct Hero
{
	string name;
	int Health=100;     //cтворюємо посилання на структуру позішену гравців
	Position position;

};

int N; //змінна для запуску циклу підрахунку героїв

vector <Hero> Heros; //створюємо вектор Heros з типом Hero


int main() 
{
	cout << "How many players do you have? ";
	cin >>N;




	for (int i = 0; i < N; i++)
	{
		Hero Myhero;
		cout << "Set name: ";
		cin >> Myhero.name;
		cout << "Set health: ";
		cin >> Myhero.Health;
		cout << "Set position x: ";
		cin >> Myhero.position.x;
		cout << "Set position y: ";
		cin >> Myhero.position.y;
		Heros.push_back(Myhero);
	}
	Meteor Mymeteor;
	cout << "The Meteor falling, set position x: ";
	cin >> Mymeteor.position.x;
	cout << "Set position y: ";
	cin >> Mymeteor.position.y;
	cout << "Set demage: ";
	cin >> Mymeteor.demage;
	cout << "Set power: ";
	cin >> Mymeteor.power;
	
	for (int i =0 ; i <Heros.size(); i++)
	{
		
		int dx = Heros[i].position.x - Mymeteor.position.x;
		int dy = Heros[i].position.y - Mymeteor.position.y;
		if (dx * dx + dy * dy <= (3 * Mymeteor.power)*(3 * Mymeteor.power))
		{
			Heros[i].Health -= Mymeteor.demage;
			cout << Heros[i].name << " Health is:"<<Heros[i].Health<<endl;
			if (Heros[i].Health<=0)
			{
				cout << Heros[i].name <<" Is dead" <<endl;
			}
		}
	}
	
	

	
	return(0);
} 