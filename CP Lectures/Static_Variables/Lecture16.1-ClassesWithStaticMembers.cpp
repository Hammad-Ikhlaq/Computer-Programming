#include<iostream>
using namespace std;

class Monster
{
private:	
	static int monstersCount;
	char name[20];
public:
	Monster();
	Monster(char*);
	void Attack();
	static int GetMonstersCount();	
	~Monster();
};
//Define and initialize static data member global scope 
int Monster::monstersCount = 0;
Monster::Monster()
{
	strcpy_s(name,"Monster");
	cout << name << " created.\n";
	monstersCount++;
}
Monster::Monster(char* monsterName)
{
	cout << monsterName << " created.\n";
	strcpy_s(name, monsterName);
	monstersCount++;
}
Monster::~Monster()
{
	cout << name << " is being destroyed.\n";
	monstersCount--;
}
void Monster::Attack()
{
	if (monstersCount < 5)
	{
		cout << name <<" is Coward.\n";
	}		
	else
	{
		cout << name <<" killed a space creature.\n";
	}
}
//Static member function cannot access any non-static member
int Monster::GetMonstersCount()
{
	//Uncomment this line and see what happens
	//strcpy(name, "abc");
	return monstersCount;
}
void main()
{
	cout << "Game Started\n";

	//Static Member Function can be called without using an objet
	//Static data exists without any objects creation
	cout << "Monsters Count:\t" << Monster::GetMonstersCount()<<endl;

	Monster m1("Water Zombie");
	m1.Attack();

	cout << "Size of m1:\t" << sizeof(m1) << endl;

	Monster* m2 = new Monster("Red Devil");
	m2->Attack();
	cout << "Mosters Count:\t" << m2->GetMonstersCount()<<endl;	//Static Members can be used using objects of class

	delete m2;
	cout << "Mosters Count:\t" << m1.GetMonstersCount()<<endl;
	
	Monster* monstersGroup = new Monster[5];

	m1.Attack();
	cout << "Mosters Count:\t" << monstersGroup->GetMonstersCount()<<endl;// What is this line doing
	delete[] monstersGroup;
	cout << "Monsters Count:\t" << Monster::GetMonstersCount() << endl;
}