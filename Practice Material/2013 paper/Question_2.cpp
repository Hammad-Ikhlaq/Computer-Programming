# include <iostream>
using namespace std;
template <typename T>
int find(T array_A[], int size_of_A, T element_to_search)
{
	for (int i = 0; i < size_of_A; i++)
	{
		if (element_to_search == array_A[i])
		{
			return i;
		}
	}
	return -1;
}
template <>
int find(char* array_A[], int size_of_A, char* element_to_search)
{
	for (int i = 0; i < size_of_A; i++)
	{
		if (strcmp(array_A[i], element_to_search) == 0)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	int a[] = { 2,3,5,8 };
	char b[] = { 'H', 'e', 'l', 'l', 'o' };
	char *c[] = { "cd", "lion", "zoo" };

	cout << "Index = " << find<int>(a, 4, 3) << endl;
	cout << "Index = " << find<char>(b, 5, 'l') << endl;
	cout << "Index = " << find<char*>(c, 3, "zoo") << endl;
	system("pause");
}