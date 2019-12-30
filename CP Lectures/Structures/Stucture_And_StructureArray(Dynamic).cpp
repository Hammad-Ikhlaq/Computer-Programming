# include <iostream>
using namespace std;

struct Wajahat
{
	int id;
	int age;
	int name;
};
int main()
{
	
	// with Heap Memory for Single Struct.....
	cout << "with Heap Memory for Single Struct.....";
	Wajahat *p1 = new Wajahat;
	p1->id = 2;
	p1->age = 2;
	p1->name = 2;
	cout << (*p1).id << "\t" << p1->id << endl;
	cout << (*p1).age << "\t" << p1->age << endl;
	cout << (*p1).name << "\t" << p1->name << endl;

	// with Heap Memory for Array of Struct.....
	cout << "with Heap Memory for Array of Struct.....";
	Wajahat *p2 = new Wajahat[5];
	for (int i = 0; i < 5; i++)
	{
		p2[i].id = i;
		p2[i].age = i;
		p2[i].name = i;
	}
	for (int j = 0; j < 5; j++)
	{
		cout << p2[j].id<< endl;
		cout << p2[j].age<< endl;
		cout << p2[j].name<< endl;
		cout << "\n\n\n";
	}
	system("pause");
}