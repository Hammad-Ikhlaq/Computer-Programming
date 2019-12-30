#include<iostream>
using namespace std;
class Tool
{
protected:
	int strength;
public:
	Tool(int a)
	{
		strength = a;
	}
	virtual char* getWhoAmI() = 0;
	bool fight(Tool&)
	{
		return true;
	}
};
class Scissors :public Tool
{
public:
	Scissors(int a) :Tool(a)
	{

	}
	bool fight(Tool&obj)
	{
	/*	if (obj.getWhoAmI=="Scissors")*/
		{
			return true;
		}
		return false;
	}
	char* getWhoAmI()
	{
		return " Scissors ";
	}
	friend ostream&operator<<(ostream&out, Scissors obj);
};
ostream&operator<<(ostream&out, Scissors obj)
{
	out << obj.strength;
	return out;
}
class Rock :public Tool
{
public:
	Rock(int a) :Tool(a)
	{

	}
	bool fight(Tool&obj)
	{
		/*if (obj.getWhoAmI == "Rock")*/
		{
			return true;
		}
		return false;
	}
	char* getWhoAmI()
	{
		return " Rock ";
	}
	friend ostream&operator<<(ostream&out, Rock obj);
};
ostream&operator<<(ostream&out, Rock obj)
{
	out << obj.strength;
	return out;
}
class Paper :public Tool
{
public:
	Paper(int a) :Tool(a)
	{

	}
	bool fight(Tool&obj)
	{
		/*if (obj.getWhoAmI == "Paper")*/
		{
			return true;
		}
		return false;
	}
	char* getWhoAmI()
	{
		return " Papers ";
	}
	friend ostream&operator<<(ostream&out, Paper obj);
};
ostream&operator<<(ostream&out, Paper obj)
{
	out << obj.strength;
	return out;
}
int main(){
	Tool*tools[3];
	Scissors s1(5);
	Paper p1(7);
	Rock r1(15);
	tools[0] = &r1;
	tools[1] = &p1;	
	tools[2] = &s1;

	int choice1 = 0, choice2 = 0;

	cout << "1: Rock (r)\n";
	cout << "2: Paper (p)\n";
	cout << "3: Scissors (s)\n";
	cout << "Enter the choices for the two contestants to fight and -1 to end:\n";
	cin >> choice1;

	// 3 2 
	// should play Scissors against paper

	while (choice1 != -1){
		cin >> choice2;
		cout << tools[choice1 - 1]->getWhoAmI() << " vs " << tools[choice2 - 1]->getWhoAmI() << endl;
		// output: Scissors vs Paper
		if (tools[choice1 - 1]->fight(*tools[choice2 - 1]))
		{
			cout << tools[choice1 - 1]->getWhoAmI() << " won! " << endl;
		}
		else {
			cout << tools[choice1 - 1]->getWhoAmI() << " lost! " << endl;
		}
		// Scissors won!
		cout << "Enter the choices for the two contestants to fight and -1 to end:\n";
		cin >> choice1;
	}
	return 0;
}
