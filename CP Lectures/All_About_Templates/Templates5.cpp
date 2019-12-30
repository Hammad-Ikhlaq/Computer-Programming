//# include <iostream>
//using namespace std;
//
//template <class T>
//
//class Wajahat
//{
//public:
//	Wajahat(T a);
//};
//template <class T>
//Wajahat <T>::Wajahat(T a)
//{
//	cout << a << " Is Not A Character\n\n";
//}
//template <>
//class Wajahat<char>
//{
//public:
//	Wajahat(char a);
//
//};
//Wajahat <char>::Wajahat(char a)
//{
//	cout << "Our Special Case :: ";
//	cout << a << " Is A Character\n\n";
//}
//int main()
//{
//	Wajahat <int> obj1(7);
//	Wajahat <int> obj2(10.7);
//	Wajahat <char> obj3('A');
//	system("pause");
//}