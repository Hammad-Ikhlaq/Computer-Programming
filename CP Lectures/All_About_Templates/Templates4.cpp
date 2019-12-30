//# include <iostream>
//using namespace std;
//
//// class templates.....
//
//template <class T1 , class T2>
//
//class Wajahat
//{
//	T1 first;
//	T2 second;
//public:
//	Wajahat(T1 a, T2 b)
//	{
//		first = a;
//		second = b;
//	}
//	T2 bigger();
//};
//
//template <class T1 , class T2>
//T2 Wajahat<T1 ,	T2>::bigger()
//{
//	if (first > second)
//	{
//		return first;
//	}
//	return second;
//}
//int main()
//{
//	// need to tell which datatype you are going to pass
//	Wajahat <int, float> w1(10, 20.22);
//	cout << w1.bigger() << endl;
//	system("pause");
//}