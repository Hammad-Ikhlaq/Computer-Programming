//#include<iostream>
//using namespace std;
//
//class Animal
//{
//private:
//	char name[30];
//public:
//	Animal();
//	Animal(char*);
//	virtual void Move();
//	char* GetName();
//	virtual ~Animal();
//};
//Animal::Animal()
//{
//	strcpy_s(name, "Dummy");
//}
//Animal::Animal(char* animalName)
//{
//	strcpy_s(name, animalName);
//}
//void Animal::Move()
//{
//	cout << name << " is MOVING.\n";
//}
//char* Animal::GetName()
//{
//	return name;
//}
//Animal::~Animal()
//{
//	cout << "~Animal() called.\n";
//}
////----------------------------------------------------------------
//class Dog : public Animal
//{
//private:
//	char type[20];
//public:
//	Dog();
//	virtual ~Dog();	//Keyword virtual is optional
//	Dog(char*, char*);
//	void Move();	//Notice this declaration...override and virtuale are optional
//};
//Dog::Dog() : Animal("Tommy")
//{
//	strcpy_s(type, "Simple");
//}
//Dog::Dog(char* dogName, char* dogType) : Animal(dogName)
//{
//	strcpy_s(type, dogType);
//}
//void Dog::Move()
//{
//	cout << GetName() << " is RUNNING.\n";
//}
//Dog::~Dog()
//{
//	cout << "~Dog() called for " << GetName() << endl;
//}
////----------------------------------------------------------------
//class Turtle : public Animal
//{
//private:
//	char mask_color[20];
//public:
//	Turtle();
//	~Turtle();	//Keyword virtual is optional
//	Turtle(char*, char*);
//	void Move(); //Notice this declaration...override and virtuale are optional
//};
//Turtle::Turtle() : Animal("Ninja")
//{
//	strcpy_s(mask_color, "Green");
//}
//Turtle::Turtle(char* turtleName, char* color) : Animal(turtleName)
//{
//	strcpy_s(mask_color, color);
//}
//void Turtle::Move()
//{
//	cout << mask_color << " " << GetName() << " is CRAWLING.\n";
//}
//Turtle::~Turtle()
//{
//	cout << "~Turtle() called for " << GetName() << endl;
//}
//
//void main()
//{
//	Animal* animals[5];
//
//	//Base Class Pointers pointing to Derived Class Objects
//	animals[0] = new Dog;
//	animals[1] = new Turtle("Donnie", "Purple");
//	animals[2] = new Dog("Poni", "Simple");
//	animals[3] = new Turtle("Leo", "Blue");
//	animals[4] = new Turtle("Mikey", "Orange");
//
//	for (int i = 0; i < 5; i++)
//	{
//		animals[i]->Move();	//Polymorphism		
//	}
//	cout << endl;
//
//	for (int i = 0; i < 5; i++)
//	{
//		delete animals[i];
//		cout << endl;
//	}
//
//	//Homework: Remove keyword virtual from Destructors and note the program behavior
//}