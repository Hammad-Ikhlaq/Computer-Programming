#include<iostream>
using namespace std;
int main()
{
	char ** s = new char *[1];
	char * name = new char[20];
	int len = strlen(name);
	strcpy_s(name,len, "John Doe");
	s[0] = name;
	//delete[] name;
	cout << s[0] << endl;
	delete[] s;
	s = nullptr;
	system("pause");
	return 0;
}