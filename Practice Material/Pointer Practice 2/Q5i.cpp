#include<iostream>
using namespace std;
void IncBy1(int * arr, int n){
	int * temp = new int[n + 1];
	for (int i = 0; i<n; i++)
		temp[i] = arr[i];
	delete[] arr;
	arr = temp;
}
int main()
{
	int * A = new int[5];
	IncBy1(A, 5);
	system("pause");
	return 0;
}