#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct node
{
	int neu,dem;
	node*next;
};
void makeList(int&level, node * &head, node *& tail,int&prev)
{

	if (level == 1&&prev==0)
	{
		head = new node;
		tail = new node;
		head->neu = 0;
		head->dem = 1;
		head->next = tail;
		tail->neu = 1;
		tail->dem = 1;
		tail->next = nullptr;
		cout << head->neu << "/" << head->dem << "  ";
		cout << tail->neu << "/" << tail->dem << "\n";
			level=level++;
	}
	else if (level == 1 && prev != 0)
	{
		head->next = tail;
		tail->next = nullptr;
		cout << head->neu << "/" << head->dem << "  ";
		cout << tail->neu << "/" << tail->dem << "\n";
			level=level++;
	}
	else if (level>1&&prev==0)
	{
		head = new node;
		tail = new node;
		head->neu = 0;
		head->dem = 1;
		head->next = tail;
		tail->neu = 1;
		tail->dem = 1;
		tail->next = nullptr;
		int i = 0;
		node*temp1 = head;
		node*temp2 = head->next;
		node*trav1 = head;
		node*trav2 = head->next;
		while (i < level-1)
		{
			temp1 = head;
			temp2 = head->next;
			trav1 = head;
			trav2 = head->next;
			while (trav2!=nullptr)
			{
				if ((trav1->dem + trav2->dem) <= level)
				{
					node*newnode = new node;
					newnode->neu = (trav1->neu + trav2->neu);
					newnode->dem = (trav1->dem + trav2->dem);
					trav1->next = newnode;
					newnode->next = trav2;
				}
				trav1 = trav2;
				trav2 = trav2->next;
			}
		i++;
		}
		node*tempprint = head;
		while (tempprint->next != nullptr)
		{
			cout << tempprint->neu << "/" << tempprint->dem << "  ";
			tempprint = tempprint->next;
		}
			cout << tail->neu << "/" << tail->dem << "\n";
				level=level++;
				prev=level;
	}
}
void increaseby1(node * &head, node *& tail, int&prev)
{
	if (prev == 0 && head == nullptr)
	{
		head = new node;
		tail = new node;
		head->neu = 0;
		head->dem = 1;
		head->next = tail;
		tail->neu = 1;
		tail->dem = 1;
		tail->next = nullptr;
		cout << head->neu << "/" << head->dem << "  ";
		cout << tail->neu << "/" << tail->dem << "\n";
		prev = prev++;
	}
	else
	{
		int i = 0;
		node*temp1 = head;
		node*temp2 = head->next;
		node*trav1 = head;
		node*trav2 = head->next;
		while (i < prev+1)
		{
			temp1 = head;
			temp2 = head->next;
			trav1 = head;
			trav2 = head->next;
			while (trav2 != nullptr)
			{
				if ((trav1->dem + trav2->dem) <= prev)
				{
					node*newnode = new node;
					newnode->neu = (trav1->neu + trav2->neu);
					newnode->dem = (trav1->dem + trav2->dem);
					trav1->next = newnode;
					newnode->next = trav2;
				}
				trav1 = trav2;
				trav2 = trav2->next;
			}
			i++;
		}
		node*tempprint = head;
		while (tempprint->next != nullptr)
		{
			cout << tempprint->neu << "/" << tempprint->dem << "  ";
			tempprint = tempprint->next;
		}
		cout << tail->neu << "/" << tail->dem << "\n";
		prev = prev++;
	}
}
void decreaseby1(node * &head, node *& tail, int&prev)
{
	if (prev == 0 && head == nullptr)
	{
		cout << "The List is already empty\n";
	}
	else if (prev==1)
	{
		head = nullptr;
		tail = nullptr;
		cout << "The List is now empty\n";
		prev = prev - 1;
	}
	else
	{
		int check = -1;
		node*temp1 = head;
		node*temp2 = head->next;
		node*temp3;
		while (temp2->next!=nullptr)
		{
			if (check==1)
			{
				temp1=temp1->next;
				temp2=temp2->next;
			}
			if (temp2->dem>=prev)
			{
				temp3=temp2;
				temp2=temp2->next;
				delete temp3;
				temp1->next=temp2;
				check=1;
			}
			else
			{
				temp1=temp1->next;
				temp2=temp2->next;
			}
		}
		node*tempprint = head;
		while (tempprint->next != nullptr)
		{
			cout << tempprint->neu << "/" << tempprint->dem << "  ";
			tempprint = tempprint->next;
		}
		cout << tail->neu << "/" << tail->dem << endl;
		prev = prev--;
	}
}
void updatelist(int&level, node * &head, node *& tail, int&prev)
{
	int loop = level - prev,check=0,i=0;
	if (loop<0) //to avoid out of bound
	{
		if ((-1*loop)>prev)
		{
			check = 1;
		}
	}
	if (prev == 0 && loop>0&&level==1)
	{
		head = new node;
		tail = new node;
		head->neu = 0;
		head->dem = 1;
		head->next = tail;
		tail->neu = 1;
		tail->dem = 1;
		tail->next = nullptr;
		prev = level;
		cout << head->neu << "/" << head->dem << "  ";
		cout << tail->neu << "/" << tail->dem << "\n";
	}
	if (prev == 0 && loop>0 && level != 1)
	{
		head = new node;
		tail = new node;
		head->neu = 0;
		head->dem = 1;
		head->next = tail;
		tail->neu = 1;
		tail->dem = 1;
		tail->next = nullptr;
		prev = level;
	}
	if (loop>0)
	{
		int i = 0;
		node*temp1 = head;
		node*temp2 = head->next;
		node*trav1 = head;
		node*trav2 = head->next;
		while (i < loop)
		{
			temp1 = head;
			temp2 = head->next;
			trav1 = head;
			trav2 = head->next;
			while (trav2 != nullptr)
			{
				if ((trav1->dem + trav2->dem) <= level)
				{
					node*newnode = new node;
					newnode->neu = (trav1->neu + trav2->neu);
					newnode->dem = (trav1->dem + trav2->dem);
					trav1->next = newnode;
					newnode->next = trav2;
				}
				trav1 = trav2;
				trav2 = trav2->next;
			}
			i++;
		}

		node*tempprint = head;
		while (tempprint->next != nullptr)
		{
			cout << tempprint->neu << "/" << tempprint->dem << "  ";
			tempprint = tempprint->next;
		}
		cout << tail->neu << "/" << tail->dem << "\n";
		prev = level;
	}
	if (prev == 0 && loop<0)
	{
		cout << "The List is already empty\n";
	}
	else if (prev == 1&&loop<0)
	{
		head = nullptr;
		tail = nullptr;
		cout << "The List is now empty\n";
		prev = level;
	}
	if (loop<0 && prev != 0&&check!=-1)
	{
		i = 0;
		while (i>loop)
		{
			int check = -1;
			node*temp1 = head;
			node*temp2 = head->next;
			node*temp3;
			while (temp2->next != nullptr)
			{
				if (check == 1)
				{
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				if (temp2->dem > level)
				{
					temp3 = temp2;
					temp2 = temp2->next;
					delete temp3;
					temp1->next = temp2;
					check = 1;
				}
				else
				{
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
			}
			i--;
		}
		node*tempprint = head;
		while (tempprint->next != nullptr)
		{
			cout << tempprint->neu << "/" << tempprint->dem << "  ";
			tempprint = tempprint->next;
		}
		cout << tail->neu << "/" << tail->dem << endl;
		prev = level;
	}
}
int main()
{
	int command;
	int level=0,prev=0;
	node*head = nullptr, *tail = nullptr; //empty list
	while (true)
	{
		cout << "1-Make a particular level of the Farey list\n";
		cout << "2-Increase the current level by 1\n";
		cout << "3-Decrease the current level by 1\n";
		cout << "4-Update the current list\n\nSelect an option\n";
		cin >> command;
		if (command==1)
		{
			cout << "Enter the level of the Farey list\n";
			cin >> level;
			makeList(level, head, tail,prev);
		}
		else if (command == 2)
		{
			increaseby1(head, tail, prev);
		}
		else if (command == 3)
		{
			decreaseby1(head, tail, prev);
		}
		else if (command == 4)
		{
			cout << "To which level do you want to update the Farey list\n";
			cin >> level;
			updatelist(level, head, tail, prev);
		}
		else
			cout << "error\n";
	}

	system("pause");
	return 0;
}