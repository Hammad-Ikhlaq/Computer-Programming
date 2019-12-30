#include<iostream>
using namespace std;
int& Now()
{
	int Where = 1;
	return Where;
}
int main() {
	int Where;
	Where = Now();
	cout << Where;
	system("pause");
	return 0;
}