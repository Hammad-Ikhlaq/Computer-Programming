# include <iostream>
using namespace std;

struct Wajahat
{
	int id;
	int age;
	int name;
};

void input_Single_Data(Wajahat *S);

void input_All_Data(Wajahat *S, int &count);

void display(Wajahat S);

void  display_All(Wajahat *S, int count);

int main()
{
	//This Code is Only For Understanding So Thats Why Taking Name as Integer
	//In order to make it as simplpe as possible....
   // Method 1....
	int id = 1, name = 1, age = 1;
	Wajahat S1 = { id,age,name };
	cout << "Data Record Of Student Using Method 1\n\n";
	display(S1);
	cout << endl << endl;

	// Method 2....
	Wajahat S2;
	S2.id = 2;
	S2.age = 2;
	S2.name = 2;
	cout << "Data Record Of Student Using Method 2\n\n";
	display(S2);
	cout << endl << endl;

	// Method 3....
	Wajahat S3 = { 3,3,3 };
	cout << "Data Record Of Student Using Method 3\n\n";
	display(S3);
	cout << endl << endl;

	// Method 4....
	cout << "Input id , age , Name Respectively\n\n";
	cin >> id >> age >> name;
	Wajahat S4 = { id, age, name };
	cout << "Data Record Of Student Using Method 4\n\n";
	display(S4);
	cout << endl << endl;

	// Method 5 By Using Input Function....
	Wajahat S5;
	input_Single_Data(&S5);
	cout << "Data Record Of Student Using Method 5\n\n";
	display(S5);

	//Method 6 Array of Structures....
	cout << "\n\nMethod 6 : Arrays Of Structure\n\n";
	cout << "Method 6 Has No Relation With The Previous Ones\n";
	cout << "Creating a new Array To Store Data\n\n";
	cout << "Just In Order To Know How to Use Array of Structs\n\n";

	int count = 0;
	Wajahat array_Of_Structure[50];
	input_All_Data(array_Of_Structure, count);
	cout << "Displaying All Student Data Saved IN Array \n\n";
	display_All(array_Of_Structure, count);

	system("pause");
}
void input_Single_Data(Wajahat *S)
{
	cout << "Method 5\n\n";
	cout << "Enter Id \n\n";
	cin >> S->id;
	cout << "Enter age \n\n";
	cin >> S->age;
	cout << "Enter name \n\n";
	cin >> S->name;
}
void input_All_Data(Wajahat *S, int &count)
{
	int check;
	while (true)
	{
		cout << "Enter 1 To Save The Data Of A Student else press Any Key" << endl;
		cin >> check;
		if (check == 1)
		{
			cout << "Enter Id \n\n";
			cin >> (*(S + count)).id;
			cout << "Enter age \n\n";
			cin >> S[count].age;
			cout << "Enter name \n\n";
			cin >> S[count].name;
			count++;
		}
		else
		{
			break;
		}
	}
}
void display(Wajahat S)
{
	cout << S.id << endl;
	cout << S.age << endl;
	cout << S.name << endl;
}
void  display_All(Wajahat *S, int count)// Student*S and Student S[] is same...
{
	for (int i = 0; i < count; i++)
	{
		cout << "Data of Student :  " << i + 1 << endl << endl;
		cout << (*(S + i)).id << endl;
		cout << (*(S + i)).age << endl;
		cout << (*(S + i)).name << endl;
		cout << "\n\n\n";
		// or S[i].id is same as (*(S + i)).id
	}
}