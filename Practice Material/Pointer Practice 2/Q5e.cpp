#include<iostream>
using namespace std;
int main()
{
int x = 5;
int* y = new int(3);
int** z = &y;
int A[5] = { 1, 2, 3, 4, 5 };
cout << *y;
cout << **z;
cout << *&x;
cout << A[4];
cout << *(A + 2);
cout << *(A + *y);
cout << A[**z];
cout << A[x];
system("pause");
return 0;
}