//#include<iostream>
//using namespace std;
//
//template<typename t>	//t is template or type parameter
//t sum(t a, t b)
//{
//	cout << "sum of t and t called." << endl;
//	return a + b;
//}
//
//template<typename t1, typename t2>	//t1 and t2 are template or type parameter
//t1 sum(t1 a, t2 b)
//{
//	cout << "sum of t1 and t2 called." << endl;
//	return a + b;
//}
//
//template<class identifier>	//identifier is template or type parameter
//identifier product(identifier a, identifier b)
//{
//	return a * b;
//}
//
//void main()
//{
//	int i = 10, j = 20, k;
//	float l = 10.5, m = 20.2, n;
//
//	k = sum<int>(i, j);
//	cout << "k = " << k << endl;
//	
//
//	n = sum<float>(l, m);
//	cout << "n = " << n << endl;
//
//	k = sum(i, j);
//	cout << "k = " << k << endl;
//
//	n = sum(l, m);
//	cout << "n = " << n << endl;
//
//	k = sum(j, m);
//	cout << "k = " << k << endl;
//
//	system("pause");
//}