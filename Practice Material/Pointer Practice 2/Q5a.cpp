#include<iostream>
using namespace std;
int main(){
	const char* what = "Is This";
	what = "Interesting";
	cout << *what;
	what = "a";
	cout << *what;
	system("pause");
	return 0;
}