#include<iostream>
using namespace std;
int main()
{
	const char* C = "hi mom";
	C[3] = 'a';
	char *const D = "hi mom";
	D = "hi dad";
	system("pause");
	return 0;
}