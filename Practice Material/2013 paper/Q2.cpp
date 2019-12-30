#include<iostream>
using namespace std;
template<typename H1, typename H2>
int find(H1 array_A[], int size_of_A, H2 element_to_search)
{
	for (int i = 0; i < size_of_A; i++)
	{
		if (array_A[i] == element_to_search)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	int a[] = { 2, 3, 5, 8 };
	char b[] = { 'H', 'e', 'l', 'l', 'o' };
	char* c[] = { "cd", "lion", "zoo" };

	cout << "Index = " << find(a, 4, 3);
	cout << "Index = " << find(b, 5, 'l');
	cout << "Index = " << find(c, 3, "lion");
	system("pause");
	return 0;
}
