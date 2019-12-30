//#include <iostream>
//using namespace std;
//template <class T>
//
//class pair1
//{
//private:
//
//    T values[2];
//	static int count;
//public:
//	pair1(T num1, T num2)
//	{
//		values[0] = num1;
//		values[1] = num2;
//		setcount();
//	}
//	T GetMax()
//	{
//		if (values[0] > values[1])
//			return values[0];
//		else
//			return values[1];
//	}
//	T GetMin();
//	static void setcount()
//	{
//		count++;
//	}
//	static int getcount()
//	{
//		return count;
//	}
//};
//
//template <class T>
//T pair1 <T>::GetMin()
//{
//	if (values[0] < values[1])
//		return values[0];
//	else
//		return values[1];
//}
//
//template <class T>
//int pair1<T> ::count = 0;
//
//int main()
//{
//	pair1 <double> myobject1(1.012, 1.01234);
//	pair1 <double> myobject2(2.012, 2.01234);
//	pair1 <double> myobject3(3.012, 3.01234);
//	cout << myobject3.getcount() << endl;
//
//	pair1 <int> myobject4(1, 1);
//	pair1 <int> myobject5(2, 4);
//	cout << myobject5.getcount() << endl;
//
//	pair1 <float> myobject6(2, 4);
//	pair1 <float> myobject7(2, 4);
//	cout << myobject7.getcount() << endl;
//
//	system("pause");
//}