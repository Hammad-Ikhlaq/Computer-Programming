# include <iostream>
using namespace std;
class Tool
{
private : 
	int strength;
public :  
	Tool(int s)
	{
		strength = s;
	}
	virtual char* getWhoAmI()
	{
		return "Dummy";
	}
	virtual bool fight(Tool & obj)
	{
		return true;
	}
	int getStrength()
	{
		return strength;
	}
};
class Rock : public Tool
{
public :
	Rock(int strength) : Tool(strength)
	{

	}
	bool fight(Tool & obj)
	{
		if (getStrength() > obj.getStrength())
		{
			return true;
		}
		return false;
	}
	char* getWhoAmI()
	{
		return "Rock";
	}
};
class Paper : public Tool
{
public : 
	bool fight(Tool & obj)
	{
		if ((getStrength() * 2.5) > obj.getStrength())
		{
			return true;
		}
		return false;
	}
	Paper(int strength) : Tool(strength)
	{

	}
	char* getWhoAmI()
	{
		return "Paper";
	}
};
class Scissors : public Tool
{
public : 
	bool fight(Tool & obj)
	{
		if ((getStrength() * 2) > obj.getStrength())
		{
			return true;
		}
		return false;
	}
	Scissors(int strength) : Tool(strength)
	{

	}
	char* getWhoAmI()
	{
		return "Scissors";
	}
};
int main() {
	Tool *tools[3];
	Scissors s1(5);
	Paper p1(7);
	Rock r1(15);
	tools[0] = &r1;
	tools[1] = &p1;	tools[2] = &s1;

	int choice1 = 0, choice2 = 0;

	cout << "1: Rock (r)\n";
	cout << "2: Paper (p)\n";
	cout << "3: Scissors (s)\n";
	cout << "Enter the choices for the two contestants to fight and -1 to end:\n";
	cin >> choice1;

	// 3 2 
	// should play Scissors against paper

	while (choice1 != -1) {
		cin >> choice2;
		cout << tools[choice1 - 1]->getWhoAmI() << " vs " << tools[choice2 - 1]->getWhoAmI() << endl;
		// output: Scissors vs Paper
		if (tools[choice1 - 1]->fight(*tools[choice2 - 1])) {
			cout << tools[choice1 - 1]->getWhoAmI() << " won! " << endl;
		}
		else {
			cout << tools[choice1 - 1]->getWhoAmI() << " lost! " << endl;
		}
		// Scissors won!
		cout << "Enter the choices for the two contestants to fight and -1 to end:\n";
		cin >> choice1;
	}
	system("pause");
}
