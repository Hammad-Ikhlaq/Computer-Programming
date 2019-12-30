# include <iostream>
using namespace std;
class Employee
{
private:
	char * fname;
	char * lname;
	int date_Y;
	int date_M;
	int date_D;
	int salary;
public:

	Employee()
	{
		fname = NULL;
		lname = NULL;
		date_Y = 0;
		date_M = 0;
		date_D = 0;
		salary = 0;
	}

	Employee(char *fN, char *lN, int dY, int dM, int dD, int s)
	{
		fname = new char[strlen(fN) + 1];
		lname = new char[strlen(lN) + 1];
		strcpy(fname, fN);
		strcpy(lname, lN);
		date_Y = dY;
		date_M = dM;
		date_D = dD;
		salary = s;
	}
	void operator=(Employee & obj)
	{
		delete fname;
		delete lname;
		fname = new char[strlen(obj.fname) + 1];
		lname = new char[strlen(obj.lname) + 1];
		strcpy(fname, obj.fname);
		strcpy(lname,obj.lname);
		date_Y = obj.date_Y;
		date_M = obj.date_M;
		date_D = obj.date_D;
		salary = obj.salary;
	}
	int getSalary()
	{
		return salary;
	}
	int getDate()
	{
		return date_Y;
	}
	char * getFirstName()
	{
		return fname;
	}
	char * getLastName()
	{
		return lname;
	}
	void displayEmp()
	{
		cout << "Employee First Name : " << fname << endl;
		cout << "Employee Last Name : " << lname << endl;
		cout << " date_Y : " << date_Y << endl;
		cout << " date_M : " << date_M << endl;
		cout << " date_D : " << date_D << endl;
		cout << " salary : " << salary << endl;
	}
	void InputEmp()
	{
		fname= new char[25];
		lname = new char[25];
		cout << "Enter Employee First Name : ";
		cin >> fname;
		cout << "\n";
		cout << "Employee Last Name : ";
		cin >> lname;
		cout << "\n";
		cout << " date_Y : ";
		cin >> date_Y;
		cout << "\n";
		cout << " date_M : ";
		cin >> date_M;
		cout << "\n";
		cout << " date_D : ";
		cin >> date_D;
		cout << "\n";
		cout << " salary : ";
		cin >> salary;
		cout << "\n";
	}
	~Employee()
	{
		delete fname;
		delete lname;
		cout << "I AM In Destructor\n\n";
	}

};


class Company
{
private:
	Employee * employees;
	int numberOfEmployees;
public:
	Company()
	{
		employees = NULL;
		numberOfEmployees = 0;
	}
	Company(int e)
	{
		numberOfEmployees = e;

		employees = new Employee[numberOfEmployees];

		for (int i = 0; i < numberOfEmployees; i++)
		{
			employees[i].InputEmp();
		}
	}
	Company(int e , Employee *&employ)
	{
		numberOfEmployees = e;

		employees = employ;
	}
	Employee & getHighPaidEmp()
	{
		int index = 0;
		int greater = employees[0].getSalary();
		for (int i = 1; i < numberOfEmployees; i++)
		{
			if (employees[i].getSalary() > greater)
			{
				greater = employees[i].getSalary();
				index = i;
			}
		}
		return employees[index];
	}
	virtual void displayAllEmp()
	{
		for (int i = 0; i < numberOfEmployees; i++)
		{
			employees[i].displayEmp();
		}
	}
	void displayEmpsWithSalaryLimit(int min, int max)
	{
		for (int i = 0; i < numberOfEmployees; i++)
		{
			if (employees[i].getSalary() >= min && employees[i].getSalary() >= max)
			{
				employees[i].displayEmp();
			}
		}
	}
	void displayEmpsWithJoingDateLimit(int min, int max)
	{
		for (int i = 0; i < numberOfEmployees; i++)
		{
			if (employees[i].getDate() >= min && employees[i].getDate() >= max)
			{
				employees[i].displayEmp();
			}
		}
	}
	void displayEmpsWithFirstName(char * fname)
	{
		for (int i = 0; i < numberOfEmployees; i++)
		{
			if (strcmp(fname, employees[i].getFirstName()) == 0)
			{
				employees[i].displayEmp();
			}
		}
	}
	void displayEmpsWithLastName(char * lname)
	{
		for (int i = 0; i < numberOfEmployees; i++)
		{
			if (strcmp(lname, employees[i].getLastName()) == 0)
			{
				employees[i].displayEmp();
			}
		}
	}
	~Company()
	{

		cout << "I AM In Destructor of Company\n\n";
	}
	

};


int main()
{
	Employee e0("1","1",1,1,1,1);
	Employee e1("2", "2", 2, 2, 2, 2);
	Employee *emp = new Employee[2];
	emp[0] = e0;
	emp[1] = e1;
	Company C(2, emp);
	C.displayAllEmp();
	system("pause");
}