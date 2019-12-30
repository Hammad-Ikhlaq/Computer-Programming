#include<iostream>
#include<fstream>
using namespace std;
char**read_file(char* f_name, int& no_of_friends)
{
	ifstream fin(f_name);
	fin >> no_of_friends;
	char**friends = new char*[no_of_friends];
	if (fin.is_open())
	{
		int flength,i=0;
		char array[50];
		fin.getline(array, 50);
		while (fin.getline(array, 50))
		{
			flength = strlen(array);
			flength = (flength / 2)+1;
			friends[i] = new char[flength];
			for (int j = 0,k=2; j < flength-1;k=k+2, j++)
			{
				friends[i][j] = array[k];
			}
			friends[i][flength - 1] = '\0';
			i++;
		}
	}
	else
	{
		cout << "Error" << endl;
	}
	fin.close();
	return friends;
}
char**update_user(char** friends, int& no_of_friends, int*&users)
{
	no_of_friends=no_of_friends++;
	int*curr = new int[no_of_friends];
	int j = 0;
	for (; j < no_of_friends; j++)
	{
		curr[j]=users[j];
	}
	j--;
	curr[no_of_friends-1] = j;
	users = curr;
	char**temp = new char*[no_of_friends];
	int i = 0;
	for (; i < no_of_friends-1; i++)
	{
		temp[i] = friends[i];
	}
	temp[no_of_friends-1] = new char[1];
	temp[no_of_friends-1][0] = '\0';
	return temp;
}
void print_friends(char** friends, int n)
{
	cout << "The friends of " << n << " are\n";
		for (int j = 0; friends[n][j] != '\0'; j++)
		{
			cout << friends[n][j]<< "  ";
		}
		cout << endl<<endl;
}
char**update_friend(char** friends, char user, char friendname)
{
	
	int count = 0,check=0;
	const char*ptruser = &user;
	int userconv = atoi(ptruser);
	for (int j = 0; friends[userconv][j] != '\0'&&check == 0; j++)
	{
		if (friends[userconv][j] == friendname)
		{
			cout << "They are already friends\n";
			check = check++;
		}
		else
			check = -1;
	}
			for (int j = 0; friends[userconv][j] != '\0'&&check == -1; j++)
			{
				count++; //counting the number of friends;
			}
			count = count + 2;
			char*temp = new char[count];
			for (int i = 0; i < count - 2; i++)
			{
				temp[i] = friends[userconv][i];
			}
			temp[count - 2] = friendname;
			temp[count - 1] = '\0';
			friends[userconv] = temp;
			count = 0;
			const char*ptrfriend = &friendname;
			int friendconv = atoi(ptrfriend);
			for (int j = 0; friends[friendconv][j] != '\0'; j++)
			{
				count++; //counting the number of friends;
			}
			count = count + 2;
			char*curr = new char[count];
			for (int i = 0; i < count - 2; i++)
			{
				curr[i] = friends[friendconv][i];
			}
			curr[count - 2] = user;
			curr[count - 1] = '\0';
			friends[friendconv] = curr;
		return friends;
}
char**delete_friend(char** friends, char user, char friendname)
{
	int count = 0;
	int flag = 0;
	const char*ptruser = &user;
	int userconv = atoi(ptruser);
	for (int j = 0; friends[userconv][j] != '\0'; j++)
	{
		if (friends[userconv][j] == friendname)
		{
			flag = 1;
		}
	}
	if (flag==0)
	{
		cout << "They are already not friends\n";
	}
	else
		{
			for (int j = 0; friends[userconv][j] != '\0'; j++)
			{
				count++; //counting the number of friends;
			}
			int tempcount = count - 1;
			char*temp = new char[count];
			for (int i = 0, j = 0; friends[userconv][i] != '\0'; i++)
			{
				if (friends[userconv][i] != friendname)
				{
					temp[j] = friends[userconv][i];
					j++;
				}
			}
			temp[tempcount] = '\0';
			friends[userconv] = temp;
		}
	count = 0;
	const char*ptrfrnd = &friendname;
	int frndconv = atoi(ptrfrnd);

	{
		for (int j = 0; friends[frndconv][j] != '\0'; j++)
		{
			count++; //counting the number of friends;
		}
		int currcount = count - 1;
		char*curr = new char[count];
		for (int i = 0, j = 0; friends[frndconv][i] != '\0'; i++)
		{
			if (friends[frndconv][i] != user)
			{
				curr[j] = friends[frndconv][i];
				j++;
			}
		}
		curr[currcount] = '\0';
		friends[frndconv] = curr;
	}
	return friends;
}
char**delete_user(char** friends, char user, int*&users ,int&n)
{
	int count = 0;
	const char*ptruser = &user;
	int userconv = atoi(ptruser);
	int*temp = new int[n-1];
	for (int i = 0, j = 0; i<n; i++)
	{
		if (users[i] != userconv)
		{
			temp[j] = users[i];
			j++;
		}
	}
	users = temp;
	for (int i = userconv; i < n; i++)
	{
		friends[i] = friends[i + 1];
	}
	friends[n - 1] = nullptr;
	delete friends[n - 1];
	n--;
	int tempcount = count - 1;
	char*curr = nullptr;
	for (int i = 0; i < n; i++)
	{
	    count = 0;
		for (int j = 0; friends[i][j] != '\0'; j++)
		{
			if (friends[i][j] != user)
			{
				count++; //counting the number of friends;
			}
		}
		tempcount = count - 1;
		curr = new char[count+1];
		for (int k = 0, j = 0; friends[i][k] != '\0'; k++)
		{
			if (friends[i][k] != user)
			{
				curr[j] = friends[i][k];
				j++;
			}
		}
		curr[count] = '\0';
		friends[i] = curr;
	}
	return friends;
}
void print_friends_of_freinds(char**friends, char user)
{
	int count = 0;
	const char*ptruser = &user;
	int userconv = atoi(ptruser);
	cout << "The friends of " << userconv << " are\n";
	for (int j = 0; friends[userconv][j] != '\0'; j++)
	{
		cout << friends[userconv][j] << "  ";
		cout << endl << endl;
	}
	int factor=1;
	for (int j = 0; friends[userconv][j] != '\0'&&factor!=0; j++)
	{
		const char*ptrfrnd = &friends[userconv][j];
		int frndconv = atoi(&ptrfrnd[0]);
		int turns = 1;
		if (frndconv<10)
		{
			turns++;
		}
		if (frndconv>=10)
		{
			turns++;
		}
		if (frndconv>=100)
		{
			turns++;
		}
		if (frndconv>=1000)
		{
			turns++;
		}
		if (frndconv>=10000)
		{
			turns++;
		}
		if (frndconv>=100000)
		{
			turns++;
		}
		if (frndconv>=1000000)
		{
			turns++;
		}
		for (int i = turns; i > 0; i--)
		{
			if (i != turns)
			{
				frndconv = frndconv / 10;
			}
			factor = frndconv % 10;
			if (factor!=0)
			{
				cout << "And The friends of " << factor << " are ";
			}
			for (int j = 0; friends[factor][j] != '\0'&&factor!=0; j++)
			{
				cout << friends[factor][j] << "  ";
			}
			cout << endl;
		}
		factor = 0;
	}
}
void print_mutual_friends(char** friends, int user1, int user2)
{
	cout << "The mutual friends of " << user1<<" and "<<user2 << " are\n";
	for (int j = 0; friends[user1][j] != '\0'; j++)
	{
		for (int k = 0; friends[user2][k] != '\0'; k++)
		{
			if (friends[user1][j] == friends[user2][k])
			{
				cout << friends[user1][j] << "  ";
			}
		}
	}
	cout << endl << endl;
}
void likely_freinds(char**friends, char user)
{
	int count = 0;
	const char*ptruser = &user;
	int userconv = atoi(ptruser);
	int factor1 = 1,factor2,factor3;
	cout << "Likely friends of are ";
	for (int j = 0; friends[userconv][j] != '\0'&&factor1 != 0; j++)
	{
		const char*ptrfrnd = &friends[userconv][j];
		int frndconv = atoi(&ptrfrnd[0]);
		int turns = 1;
		if (frndconv<10)
		{
			turns++;
		}
		if (frndconv >= 10)
		{
			turns++;
		}
		if (frndconv >= 100)
		{
			turns++;
		}
		if (frndconv >= 1000)
		{
			turns++;
		}
		if (frndconv >= 10000)
		{
			turns++;
		}
		if (frndconv >= 100000)
		{
			turns++;
		}
		if (frndconv >= 1000000)
		{
			turns++;
		}
		for (int i = turns; i > 0; i--)
		{
			if (i != turns)
			{
				frndconv = frndconv / 10;
			}
			factor1 = frndconv % 10;
			factor2 = (frndconv / 10) % 10;
			factor3 = (frndconv / 100) % 10;
			if (factor1 != 0)
			{
				for (int j = 0; friends[factor1][j] != '\0'; j++)
				{
					for (int k = 0; friends[factor2][k] != '\0'; k++)
					{
						for (int i = 0; friends[factor2][i] != '\0'; i++)
						{
							if (friends[factor1][j] == friends[factor2][k] || friends[factor1][j] == friends[factor3][i] || friends[factor2][k] == friends[factor3][i])
							{
								cout << friends[factor1][j] << "  ";
							}
							break;
						}
					}
				}
				cout << endl;
				break;
			}
		}
		factor1 = 0;
	}
}
void save(char** friends, char*f_name, int*users, int no_of_friends)
{
	ofstream fout(f_name);
	fout<< no_of_friends<<endl;
		for (int j = 0; j < no_of_friends; j++)
		{
			fout << users[j];
			for (int k = 0; friends[j][k]!='\0'; k++)
			{
				if (friends[j][k + 1] == '\0')
				{
					fout <<","<< friends[j][k] ;
				}
				else if (friends[j][k] == '\0')
				{
					fout << friends[j][k];
				}
				else
					fout <<","<< friends[j][k];
			}
			fout << endl;
		}
		fout << endl;
}
int main()
{
	int n;
	int command;
	int*users=nullptr;
	char**friends = read_file("Friendinfo.txt",n);
	users = new int[n];
	for (int i = 0; i < n; i++)
	{
		users[i] = i;
	}
	while (true)
	{
		cout << "i) Add new user\nii) Make friends\niii) Remove friends\niv) Remove User\nv) Print Friends\nvi) Print Friends of Friends";
		cout << "\nvii) Print Mutual Friends\nviii) Print Likely Friends\nix) Save\n";
		cout << n << endl;
		for (int j = 0; j < n; j++)
		{
			cout << users[j];
			for (int k = 0; friends[j][k] != '\0'; k++)
			{
				if (friends[j][k + 1] == '\0')
				{
					cout << "," << friends[j][k];
				}
				else if (friends[j][k] == '\0')
				{
					cout << friends[j][k];
				}
				else
					cout << "," << friends[j][k];
			}
			cout << endl;
		}
		cout << endl;
		cin >> command;
		system("pause");
		system("cls");
		if (command == 1)
		{
			system("cls");
			friends = update_user(friends, n,users);
			cout << "i) Add new user\nii) Make friends\niii) Remove friends\niv) Remove User\nv) Print Friends\nvi) Print Friends of Friends";
			cout << "\nvii) Print Mutual Friends\nviii) Print Likely Friends\nix) Save\n";
			cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
			//cout << "Updated users are\n";
			//for (int i = 0; i < n; i++)
			//{
			//	cout << users[i] << endl;
			//}
			//cout << "updated friends are\n";
			//for (int i = 0; i < n; i++)
			//{
			//	for (int j = 0; friends[i][j] != '\0'; j++)
			//	{
			//		cout << friends[i][j];
			//	}
			//	cout << endl;
			//}
		}
		else if (command == 2)
		{
			char user;
			char friendname;
			system("cls");
			cout << endl << "Whose friend do you want to add\n";
			cin >> user;
			cout << endl << "Whose do you want to add as friend\n";
			cin >> friendname;
			update_friend(friends, user, friendname);
			cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
			//cout << "The updated friends are\n";
			//for (int i = 0; i < n; i++)
			//{
			//	for (int j = 0; friends[i][j] != '\0'; j++)
			//	{
			//		cout << friends[i][j];
			//	}
			//	cout << endl;
			//}
		}
		else if (command == 3)
		{
			char user;
			char friendname;
			system("cls");
			cout << endl << "Whose friend do you want to delete\n";
			cin >> user;
			cout << endl << "Which friend do you want to delete\n";
			cin >> friendname;
			delete_friend(friends, user, friendname);
			cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
			//cout << "The updated friends are\n";
			//for (int i = 0; i < n; i++)
			//{
			//	for (int j = 0; friends[i][j] != '\0'; j++)
			//	{
			//		cout << friends[i][j];
			//	}
			//	cout << endl;
			//}
		}
		else if (command == 4)
		{
			char user;
			system("cls");
			cout << endl << "Which user do you want to delete\n";
			cin >> user;
			delete_user(friends, user, users,n);
			cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
			//cout << "Updated users are\n";
			//for (int i = 0; i < n; i++)
			//{
			//	cout << users[i] << endl;
			//}
			//cout << "The updated friends are\n";
			//for (int i = 0; i < n; i++)
			//{
			//	for (int j = 0; friends[i][j] != '\0'; j++)
			//	{
			//		cout << friends[i][j];
			//	}
			//	cout << endl;
			//}
		}
		else if (command == 5)
		{
			int z;
			system("cls");
			cout << endl << "Friends of whom do you want to print\n";
			cin >> z;
			print_friends(friends, z);
			cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
		}
		else if (command == 6)
		{
			char z;
			system("cls");
			cout << endl << "Friends of Friends of whom do you want to print\n";
			cin >> z;
			system("cls");
			print_friends_of_freinds(friends, z);
			cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
		}
		else if (command == 7)
		{
			int user1,user2;
			system("cls");
			cout << endl << "Enter both the users whom mutual friends do you want to print\n";
			cin >> user1;
			cin >> user2;
			system("cls");
			print_mutual_friends(friends, user1, user2);
			cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
		}
		else if (command == 8)
		{
			char z;
			system("cls");
			cout << endl << "Likely Friends of whom do you want to print\n";
			cin >> z;
			system("cls");
			likely_freinds(friends, z);
						cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				cout << users[j];
				for (int k = 0; friends[j][k] != '\0'; k++)
				{
					if (friends[j][k + 1] == '\0')
					{
						cout << "," << friends[j][k];
					}
					else if (friends[j][k] == '\0')
					{
						cout << friends[j][k];
					}
					else
						cout << "," << friends[j][k];
				}
				cout << endl;
			}
			system("pause");
			system("cls");
		}
		else if (command == 9)
		{
			save(friends, "Friendinfo.txt", users, n);
		}
	}
	system("pause");
	return 0;
}