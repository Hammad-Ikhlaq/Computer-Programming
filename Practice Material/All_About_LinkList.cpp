#include <iostream>
using namespace std;

struct Node
{
	int x;
	Node * next;
};

void add_First_Item(Node *&LinkList);

void add_In_Start(Node *&LinkList);

void add_In_End(Node *&LinkList);

void add_Any_Where(Node *&LinkList);

void display(Node *LinkList);

Node* Search(Node*LinkList , int Number);

void Delete_If_Single_Node(Node *&LinkList);

void Delete_Node_From_Start(Node *&LinkList);

void Delete_Node_From_End(Node *&LinkList);

void delete_Any_Where(Node *&LinkList);

int length_Of_LinkList(Node*LinkList);

void delete_LinkList(Node*&LinkList);

void main()
{
	// To Know The Size Of A Structure .....
	cout << "Size Of Structure  ....\n\n";
	cout << sizeof(Node) << endl << endl;

	// Step 1....
	cout << "Step 1 ....\n\n";
	Node n1;
	Node n2;
	n1.x = 1;
	n1.next = &n2;
	n2.x = 2;
	n2.next = NULL;
	cout << n1.x << endl;
	cout << n1.next << endl;
	cout << n2.x << endl;
	cout << n2.next << endl << endl;

	// Step 2.....
	cout << "Step 2 ....\n\n";
	Node A;
	Node B;
	A = {1,&B};
	B = { 2,NULL};
	cout << A.x << endl;
	cout << A.next << endl;
	cout << B.x << endl;
	cout << B.next << endl << endl;

	// Step 3.....
	cout << "Step 3 ....\n\n";
	
	Node C = { 100,NULL};
	Node D = { 200,&C};
	cout << C.x << endl;
	cout << C.next << endl;
	cout << D.x << endl;
	cout << D.next << endl << endl;

	// Step 4.....
	// Giving The Address Of A LinkList To Pointer....
	cout << "Step 4 ....\n\n";
	Node *E = &D;
	cout << E->x << endl;
	cout << E->next << endl;
	cout << E->next->x << endl;
	cout << E->next->next << endl;

	// Step 5.....
	cout << "Step 5 ....\n\n";
	Node *F = new Node;
	Node *G = new Node;
	F->x = 1;
	F->next = G;
	G->x =  2;
	G->next = NULL;
	E = F;
	cout << E->x << endl;
	cout << E->next << endl;
	cout << E->next->x << endl;
	cout << E->next->next << endl << endl;

	// Step 6.....Adding A Element/Node In LinkList When It Is Empty....
	cout << "Step 6 Adding A Element/Node In LinkList When It Is Empty\n\n";
	Node *LinkList;
	add_First_Item(LinkList);
	//display(LinkList);

	// Step 7.....Adding A Element/Node In The Start of LinkList....
	cout << "Step 7 Adding A Element/Node In The Start Of LinkList\n\n";
	add_In_Start(LinkList);
	//display(LinkList);

	cout << "Step 8 Adding A Element/Node In The End Of LinkList\n\n";
	// Step 8.....Adding A Element/Node In The End Of LinkList....
	add_In_End(LinkList);
	display(LinkList);
	
	cout << "Step 9 Adding A Element/Node Any Where You Want In The LinkList\n\n";
	// Step 9.....Adding A Element/Node Any Where You Want In The LinkList....
	add_Any_Where(LinkList);

	cout << "Step 10 Display\n\n";
	// Displaying At The End......
	display(LinkList);

	cout << "Step 11 Search A Number\n\n";
	int Number;
	cout << "Enter A Number You Want To Search\n\n";
	cin >> Number;
	Node *ptr = Search(LinkList, Number);
	if (ptr != NULL)
	{
		cout << "Found" << endl;
		cout << ptr->x << endl;
	}
	else
	{
		cout << "Not Found" << endl;
	}

	cout << "Step 12 Deleting A Node When Only A Single Node is there\n"
		"Call This Function When Required It Is Commented Now....\n\n";

	// Deleting A Node When Only A Single Node is there...
	// Call This Function
	//Delete_If_Single_Node(LinkList);


	cout << "Step 13 Deleting A Node From Start\n"
		"Call This Function When Required It Is Commented Now....\n\n";
	// Deleting A Node From Start......
	//Delete_Node_From_Start(LinkList);


	cout << "Step 14 Deleting A Node From End\n"
		"Call This Function When Required It Is Commented Now....\n\n";
	// Deleting A Node From End......
	//Delete_Node_From_End(LinkList);

	cout << "Step 15 Deleting A Node From Your Desired Position\n\n";
	delete_Any_Where(LinkList);
	display(LinkList);

	cout << "Step 16 Length Of A Link List.....\n\n";
	cout << length_Of_LinkList(LinkList) << endl;

	cout << "Step 17 Deleting Complete LinkListNode\n\n";
	delete_LinkList(LinkList);
	display(LinkList);

	system("pause");
}

void add_First_Item(Node *&LinkList)
{
	Node *temp = new Node;
	cout << "Enter A Number \n\n";
	cin >> temp->x;
	temp->next = NULL;
	LinkList = temp;
}

void add_In_Start(Node *&LinkList)
{
	if (LinkList == NULL)
	{
		add_First_Item(LinkList);
	}
	else
	{
		Node *temp = new Node;
		cout << "Enter A Number \n\n";
		cin >> temp->x;
		temp->next = LinkList;
		LinkList = temp;
	}
}

void add_In_End(Node *&LinkList)
{
	Node *temp = new Node;
	temp = LinkList;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	Node *add = new Node;
	cout << "Enter A Number \n\n";
	cin >> add->x;
	temp->next = add;
	add->next = NULL;
}

void add_Any_Where(Node *&LinkList)
{
	Node *temp = new Node;
	int Position;
	cout << "Enter A Position"<< endl;
	cin >> Position;

	if (Position == 1 || Position == 0)
	{
		add_In_Start(LinkList);
	}
	else
	{
		temp = LinkList;
		Node *add = new Node;
		cout << "Enter A Number \n\n";
		cin >> add->x;
		for (int i = 1; i < Position - 1; i++)
		{
			temp = temp->next;
		}

		add->next = temp->next;
		temp->next = add;
	}
}

void display(Node *LinkList)
{
	cout << "Displaying The Whole List Till Saved\n\n";
	while (LinkList!= NULL)
	{
		cout << LinkList->x << endl;
		LinkList = LinkList->next;
	}
}
Node* Search(Node*LinkList, int Number)
{
	Node *LinkList1 = new Node;
	LinkList1 = LinkList;
	while (LinkList1 != NULL)
	{
		if (LinkList1->x == Number)
		{
			return LinkList1;
		}
		LinkList1 = LinkList1->next;
	}
	return 0;
}
void Delete_If_Single_Node(Node *&LinkList)
{
	delete LinkList;
	LinkList = NULL;
}
void Delete_Node_From_Start(Node *&LinkList)
{
	Node *temp;
	temp = LinkList -> next;
	delete LinkList;
	LinkList = temp;
}
void Delete_Node_From_End(Node *&LinkList)
{
	Node *temp;
	Node *temp1;
	temp = LinkList;
	temp1 = LinkList->next;
	while (temp1 -> next != NULL)
	{
		temp1 = temp1->next;
		temp = temp->next;
	}
	delete temp1;
	temp1 = NULL;
	temp->next = NULL;
}
void delete_Any_Where(Node *&LinkList)
{
	int Position;
	cout << "Enter A Position To Delete" << endl;
	cin >> Position;

	if (Position == 1 || Position == 0)
	{
		Delete_Node_From_Start(LinkList);
	}
	else
	{
		Node *temp;
		temp = LinkList;
		for (int i = 1; i < Position - 1; i++)
		{
			temp = temp->next;
		}
		Node *p = temp->next->next;
		delete temp->next;
		temp->next = p;
	}
}
int length_Of_LinkList(Node*LinkList)
{
	int count = 0;
	while (LinkList != NULL)
	{
		LinkList = LinkList->next;
		count++;
	}
	return count;
}
void delete_LinkList(Node*&LinkList)
{
	Node *temp;
	while (LinkList != NULL)
	{
		temp = LinkList->next;
		delete LinkList;
		LinkList = temp;
	}

	// Second Method For Deleting A LinkList.......
	/*Node *temp;
	while (LinkList ->next != NULL)
	{
		temp = LinkList ->next;
		delete LinkList;
		LinkList = temp;
	}
	delete LinkList;
	LinkList = NULL;*/
	
}