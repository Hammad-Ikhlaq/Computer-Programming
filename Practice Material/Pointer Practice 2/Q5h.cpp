#include<iostream>
using namespace std;
int main()
{
	int meaning = 42;
	int *life = &meaning;
	int **universe = &life;
	int ***everything = &universe;
	cout << ***everything << endl;
	delete life;
	life = nullptr;
	universe = nullptr;
	everything = nullptr;
	system("pause");
	return 0;
}