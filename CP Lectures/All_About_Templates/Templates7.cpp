//#include <iostream>
//#include <string>
//using namespace std;
//
//class Dog
//{
//private :
//	char name[20];
//public :
//	Dog();
//	Dog(char*);
//	char* GetName()
//	{
//		return name;
//	}
//};
//
//Dog::Dog()
//{
//	strcpy_s(name, "Tommy");
//}
//Dog::Dog(char* n)
//{
//	strcpy_s(name, n);
//}
//
//template<class T>
//class Stack
//{
//private:
//	int size;
//	T* myArray;
//	int top;
//
//public:
//	Stack(int);
//	~Stack();
//	bool IsEmpty() 
//	{ 
//		return (top == -1);
//	}
//	bool IsFull() 
//	{ 
//		return (top == size - 1);
//	}
//	T Pop();
//	void Push(T);
//};
//
//template<class T>	//Template 
//Stack<T>::Stack(int s=10)
//{
//	size = s;
//	top = -1;
//
//	if (size > 0)
//		myArray = new T[size];
//	else
//		myArray = 0;
//}
//template<class T>
//Stack<T>::~Stack()
//{
//	if (myArray)
//		delete[] myArray;
//}
//template<class T>
//T Stack<T>::Pop()
//{
//	if (!IsEmpty())
//	{
//		T return_value = myArray[top];
//		top--;
//		return return_value;
//	}
//	else
//	{
//		cout << "Stack is Empty.\n";
//		return 0;
//	}
//}
//
//template<class T>
//void Stack<T>::Push(T element)
//{
//	if (!IsFull())
//	{
//		top++;
//		myArray[top] = element;
//	}
//	else
//	{
//		cout << "Stack is Full.\n";
//	}
//
//}
//
//void main()
//{
//	Stack<int> intStack(3);
//
//	intStack.Pop();
//
//	intStack.Push(5);
//	intStack.Push(10);
//	intStack.Push(15);
//	intStack.Push(20);
//
//	cout << "Pop Element:\t" << intStack.Pop() << endl;
//	cout << "Pop Element:\t" << intStack.Pop() << endl;
//	cout << "Pop Element:\t" << intStack.Pop() << endl;
//	cout << "Pop Element:\t" << intStack.Pop() << endl;
//
//	cout << "\n\n\nTest next Stack\n\n\n";
//
//	Stack<Dog*> dogStack(3);
//
//	dogStack.Pop();
//
//	dogStack.Push(new Dog("tony"));
//	dogStack.Push(new Dog("popi"));
//	dogStack.Push(new Dog("dolly"));
//	dogStack.Push(new Dog("jojo"));
//
//	cout << "Pop Element:\t" << dogStack.Pop()->GetName() << endl;
//	cout << "Pop Element:\t" << dogStack.Pop()->GetName() << endl;
//	cout << "Pop Element:\t" << dogStack.Pop()->GetName() << endl;
//
//	cout << "\n\n\nTest next Stack\n\n\n";
//
//	Stack<char*> dogStack2(3);
//
//	dogStack2.Pop();
//
//	dogStack2.Push("tony");
//	dogStack2.Push("popi");
//	dogStack2.Push("dolly");
//
//	cout << "Pop Element:\t" << dogStack2.Pop() << endl;
//	cout << "Pop Element:\t" << dogStack2.Pop() << endl;
//	cout << "Pop Element:\t" << dogStack2.Pop() << endl;
//	//cout << "Pop Element:\t" << dogStack.Pop()->GetName() << endl;
//	//Why this program crashed and how can you fix it?
//	system("pause");
//}