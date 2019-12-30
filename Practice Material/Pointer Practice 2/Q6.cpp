#include<iostream>
using namespace std;
int main()
{
	int a , b , c , d ;
	cout << "Enter the value of a\n";
	cin >> a;
	cout << "Enter the value of b\n";
	cin >> b;
	cout << "Enter the value of c\n";
	cin >> c;
	cout << "Enter the value of d\n";
	cin >> d;
	int*ptra = &a, *ptrb = &b, *ptrc = &c, *ptrd = &d;
	int*ptrtemp = NULL;
	ptrtemp = ptra;
	ptra = ptrd;
	ptrd = ptrc;
	ptrc = ptrb;
	ptrb = ptrtemp;
	cout << *ptra << *ptrb << *ptrc << *ptrd;
	system("pause");
	return 0;
}