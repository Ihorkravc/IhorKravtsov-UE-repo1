#include <iostream>
#include <map>;
using namespace std;



// Оголошення змінних
int N;
map<int,int>MYclan;


int main() {

	// ввести N
    cout << "Write number N:";
    cin >>   N;



	for (int i = 0; i < N; i++)
	{
		int type, add;
        cout << "Write number of type:";
		cin >> type >> add;
		MYclan[type] += add;

	}
    int maxType, minType;
    int maxCount, minCount;
    bool first = true;

    for (auto pair : MYclan) {
        int type = pair.first;
        int count = pair.second;

        if (first) {
            maxType = minType = type;
            maxCount = minCount = count;
            first = false;
        }
        else {
            if (count > maxCount) {
                maxCount = count;
                maxType = type;
            }

            if (count < minCount) {
                minCount = count;
                minType = type;
            }
        }
    }
   
    cout << "Min count: " << minCount << endl;
    cout << "Max count: " << maxCount << endl;

    return 0; }

	

