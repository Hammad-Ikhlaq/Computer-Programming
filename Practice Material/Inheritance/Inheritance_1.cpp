#include<iostream>
using namespace std;

//----------
//Employee Class
//----------
class Employee
{
private:
	char name[50];
	char cnic[20];
public:
	Employee();
	Employee(char*, char*);
	void PrintInfo();
	void SetValues(char*, char*);
	char* GetName();
	~Employee();
};
char* Employee::GetName()
{
	return name;
}
Employee::Employee()
{
	cout << "Employee Default Constructor Called\n";
	strcpy_s(name, "");
	strcpy_s(cnic, "");
}
Employee::Employee(char* empName, char* nic)
{
	strcpy_s(name, empName);
	strcpy_s(cnic, nic);
	cout << "Employee Overloaded Constructor Called for " << name << endl;
}
Employee::~Employee()
{
	cout << "Employee Destructor Called for " << name << endl;
	system("pause");
}

void Employee::PrintInfo()
{
	cout << "Name:\t" << name << endl;
	cout << "CNIC:\t" << cnic << endl;
}
void Employee::SetValues(char* empName, char* nic)
{
	strcpy_s(name, empName);
	strcpy_s(cnic, nic);
}
//-----------------------------------------------------------------------------------------
//HourlyWorker Class
//-----------------------------------------------------------------------------------------
class HourlyWorker : public Employee	//Member Access Specifier is Public. This is Public Inheritance
{
private:
	int workingHours;
	int wagePerHour;
public:
	HourlyWorker();
	HourlyWorker(char*, char*, int, int);
	void SetValues(char*, char*, int, int);	//This is function Overloading not Overriding as parameters list is different from Base Class' SetValues
	~HourlyWorker();
	void PrintInfo();	//This is function overriding as name and function parameters are same as that of base class
	int CalculatePay();	//HourlyWorker Specific Function
};
int HourlyWorker::CalculatePay()
{
	return workingHours * wagePerHour;
}
void HourlyWorker::PrintInfo()
{
	//PrintInfo();//This is recursive call i.e. function calling itself.
	Employee::PrintInfo();	//We need to call parent's PrintInfo
	cout << "Total Working Hours :\t" << workingHours << endl;
	cout << "Wage per Hour :\t" << wagePerHour << endl;
	cout << "Total Payment:\t" << CalculatePay() << endl;
}
HourlyWorker::HourlyWorker()
{
	cout << "HourlyWorker Default Constructor Called\n";
	workingHours = wagePerHour = 0;
}
HourlyWorker::~HourlyWorker()
{
	cout << "HourlyWorker Destructor Called for " << GetName() << endl;
	system("pause");
}
HourlyWorker::HourlyWorker(char* empName, char* nic, int workHrs, int wPh) :Employee(empName, nic)
{
	cout << "HourlyWorker Overloaded Constructor Called.\n";
	workingHours = workHrs;
	wagePerHour = wPh;
}
void HourlyWorker::SetValues(char* empName, char* nic, int workHrs, int wPh)
{
	Employee::SetValues(empName, nic); //Notice this function call
	workingHours = workHrs;
	wagePerHour = wPh;
}
//-----------------------------------------------------------------------------------------
//SalariedEmployee Class
//-----------------------------------------------------------------------------------------
class SalariedEmployee : public Employee
{
private:
	int salary;
public:
	SalariedEmployee();
	SalariedEmployee(char*, char*, int);
	void SetValues(char*, char*, int);	//Overloaded Function
	~SalariedEmployee();
	void PrintInfo();	//This is Function Overriding
};
SalariedEmployee::SalariedEmployee()
{
	cout << "SalariedEmployee Default Constructor Called\n";
	salary = 0;
}
SalariedEmployee::SalariedEmployee(char* empName, char* nic, int income) :Employee(empName, nic)
{
	cout << "SalariedEmployee Overloaded Constructor Called.\n";
	salary = income;
}
void SalariedEmployee::SetValues(char* empName, char* nic, int income)
{
	Employee::SetValues(empName, nic);
	salary = income;
}
SalariedEmployee::~SalariedEmployee()
{
	cout << "SalariedEmployee Destructor Called for " << GetName() << endl;
	system("pause");
}
void SalariedEmployee::PrintInfo()
{
	Employee::PrintInfo();
	cout << "Total Payment:\t" << salary << endl;
}
void main()
{
	//Test (Uncomment) following test cases one by one


	// Test 1 - Test Creation of object using default constructors
	HourlyWorker hw1;
	cout << "\n\n\n";
	system("pause");
	// Test 2
	HourlyWorker hw2;
	hw2.SetValues("abc xyz", "1234567890", 50, 1000);
	cout << "\n\n\n";
	hw2.PrintInfo();
	cout << "\n\n\n";
	system("pause");

	// Test 3 - Calling Set Values of Base Class
	HourlyWorker hw3;
	hw3.Employee::SetValues("abc xyz", "1234567");
	cout << "\n\n\n";
	hw3.PrintInfo();
	cout << "\n\n\n";
	system("pause");

	//Test 4 - Test Inherited Behavior
	HourlyWorker hw4;
	hw4.SetValues("abc xyz", "1234567890", 50, 1000);
	cout << "\n\n\n";
	cout << "Name:\t" << hw4.GetName() << endl;	//GetName has been inherited from Parent Class
	cout << "\n\n\n";
	system("pause");

	//Test 5 - Calling Parent's PrintInfo using Child Object
	HourlyWorker hw5;
	hw5.SetValues("abc xyz", "1234567890", 50, 1000);
	cout << "\n\n\n";
	hw5.Employee::PrintInfo();
	cout << "\n\n\n";
	system("pause");

	//Test 6 - Overloaded Constructors
	SalariedEmployee se1("dummy employee", "111222333", 50000);
	cout << "\n\n\n";
	se1.PrintInfo();
	cout << "\n\n\n";
	system("pause");
}