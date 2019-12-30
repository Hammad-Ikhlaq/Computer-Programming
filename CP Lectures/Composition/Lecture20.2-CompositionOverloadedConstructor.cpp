#include<iostream>
using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int, int, int);
	Date(Date&);
	Date& operator=(Date&);
	//Do we need a destructor for this class?
	~Date();
	void Print();
};
Date::Date()
{
	cout << "Date Default Constructor Called.\n";
	day = month = 1;
	year = 1960;
}
Date::Date(int d, int m, int y)
{	
	day = d;
	month = m;
	year = y;
	cout << "Date Overloaded Constructor Called for ";
	Print(); // What is this line doing?
}
Date::Date(Date& rhs)
{
	//Do we need this Copy Constructor?
	cout << "Date Copy Constructor Called to create a copy of ";
	rhs.Print();

	day = rhs.day;
	month = rhs.month;
	year = rhs.year;
}
Date& Date::operator=(Date& rhs)
{
	//Do we need this assignment operator?
	cout << "Date Assignment Operator Calles\n";
	//Are we missing something here?
	day = rhs.day;
	month = rhs.month;
	year = rhs.year;

	return *this;
}
void Date::Print()
{
	cout << day << "/" << month << "/" << year << endl;
}
Date::~Date()
{
	cout << "Date Destructor called for ";
	Print(); // What is this line doing?
}
class Employee
{
private:
	char name[50];
	char designation[20];
	Date dob;
	Date joiningDate;
public:
	Employee();
	Employee(char*, char*, Date, Date);
	void PrintInfo();
	void SetValues(char*, char*, Date, Date);
	//Do we need a destructor in this class?
	~Employee();
};
Employee::Employee()
{
	cout << "Employee Default Constructor Called\n";
	strcpy_s(name, "");
	strcpy_s(designation, "");	
}
Employee::Employee(char* empName, char* rank, Date birthDay, Date joinDate) : dob(birthDay), joiningDate(joinDate)
{
	strcpy_s(name, empName);
	strcpy_s(designation, rank);
	cout << "Employee Overloaded Constructor Called for\n";
	PrintInfo();
}
Employee::~Employee()
{
	cout << "Employee Destructor Called for " << name << endl;	
}

void Employee::PrintInfo()
{
	cout << "Name:\t" << name << endl;
	cout << "Designation:\t" << designation << endl;
	//cout << "Date of Birth:\t" << dob << endl;//How can we make this line run?
	cout << "Date of Birth:\t";
	dob.Print();
	cout << "Joining Date:\t";
	joiningDate.Print();
	cout << endl << endl << endl;
}
void Employee::SetValues(char* empName, char* rank , Date birthDay , Date joinDate)
{
	strcpy_s(name, empName);
	strcpy_s(designation, rank);
	dob = birthDay; //What is this line doing?
	joiningDate = joinDate;	//What is this line doing?
}
void main()
{
	Date bDay(24, 7, 1949);
	Date hireDate(12, 3, 1989);

	Employee boss("Peter", "Boss", bDay, hireDate);
	
	cout << "\n\n\n\nBoss Information:\n";
	boss.PrintInfo();
}