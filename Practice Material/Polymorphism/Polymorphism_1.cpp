#include<iostream>
using namespace std;

class Animal
{
private:
	char name[20];
public:
	Animal();
	Animal(char*);
	void Move();
	char* GetName();
};
Animal::Animal()
{
	strcpy_s(name, "Dummy");
}
Animal::Animal(char* animalName)
{
	strcpy_s(name, animalName);
}
void Animal::Move()
{
	cout << name << " is MOVING.\n";
}
char* Animal::GetName()
{
	return name;
}

class Dog : public Animal
{
private:
	char type[20];
public:
	Dog();
	Dog(char*, char*);
	void Move();
};
Dog::Dog() : Animal("Tommy")
{
	strcpy_s(type, "Simple");
}
Dog::Dog(char* dogName, char* dogType) : Animal(dogName)
{
	strcpy_s(type, dogType);
}
void Dog::Move()
{
	cout << GetName() << " is RUNNING.\n";
}

void main()
{
	Animal a1;
	a1.Move();

	cout << endl << endl << endl;

	Animal* aPtr = &a1;
	aPtr->Move();

	Dog d1;
	d1.Move();

	cout << endl << endl << endl;

	Dog* dPtr = &d1;
	dPtr->Move();

	cout << endl << endl << endl;
}