# include <iostream>
using namespace std;

struct Song;

void insert(Song *ptrArray, int &count);

void initializer(Song *&ptrArray);

void display(Song *ptrArray);

void displayAll(Song *ptrArray[], int count);

void remove_Single_Item(Song *&ptrArray);

void remove_All(Song *ptrArray[], int count);

void Reset(Song *ptrArray[], int &count);

int main()
{
	//creating an array of 100 pointers and initializing by NULL...
	Song **ptrArray = new Song*[100];
	for (int i = 0; i < 100; i++)
	{
		ptrArray[i] = NULL;
	}

	int perform, count = 0, index;
	// This While Loop Will Work As Menu Bar...
	// Which Will Give User The Freedom What User Will Choose...
	cout << "Enter 1 To Add A New Item (Song Detail) \n\n";
	cout << "Enter 2 In Order To Display Contents of any Saved Song\n\n";
	cout << "Enter 3 In Order To Display The Content Of All The Songs\n\n";
	cout << "Enter 4 In Order To Remove Any Item\n\n";
	cout << "Enter 5 In Order To Remove All The Items\n\n";
	cout << "Enter -1 Key To Exit The Program\n\n";
	while (true)
	{
		cout << "Enter What Do You Want To Perform\n\n";
		cin >> perform;
		if (perform == 1)
		{
			initializer(ptrArray[count]);
			insert(ptrArray[count], count);
		}
		else if (perform == 2)
		{
			cout << "Enter Index Of Which You Want To See The Data\n\n";
			cin >> index;
			display(ptrArray[index]);
		}
		else if (perform == 3)
		{
			displayAll(ptrArray, count);
		}
		else if (perform == 4)
		{
			cout << "Enter Index for Which You Want To remove The Data\n\n";
			cin >> index;
			remove_Single_Item(ptrArray[index]);

			// reset function will reset the Array Of Structure after
			// the removal of Single Song Data from Anyhere ....
			Reset(ptrArray, count);
		}
		else if (perform == 5)
		{
			remove_All(ptrArray, count);
		}
		else if (perform == -1)
		{
			break;
		}
		else
		{
			cout << "Please Give Valid Input\n\n";
		}

	}

	system("pause");
}

struct Song
{
	int track_Number;
	char artist_Name[50];
	int year_Of_Release;
};

void insert(Song *ptrArray, int &count)
{
	cout << "Enter Track Number\n\n";
	cin >> ptrArray->track_Number;

	cout << "Enter Artist Name\n\n";
	cin >> ptrArray->artist_Name;

	cout << "Enter Year Of Release\n\n";
	cin >> ptrArray->year_Of_Release;

	count++;
}

void initializer(Song *&ptrArray)
{
	ptrArray = new Song;
}

void display(Song *ptrArray)
{
	cout << "Track Number Is : \t" << ptrArray->track_Number << endl << endl;
	cout << "Artist Name Is : \t" << ptrArray->artist_Name << endl << endl;
	cout << "Year Of Release Is : \t" << ptrArray->year_Of_Release << endl << endl;
}

void displayAll(Song *ptrArray[], int count)
{
	for (int i = 0; i < count; i++)
	{
		if (ptrArray[i] != NULL)
		{
			cout << "Displaying The Data Of Song : " << i + 1 << endl << endl;
			cout << "Track Number Is : \t" << ptrArray[i]->track_Number << endl;
			cout << "Artist Name Is : \t" << ptrArray[i]->artist_Name << endl;
			cout << "Year Of Release Is : \t" << ptrArray[i]->year_Of_Release << endl;
			cout << endl << endl;
		}
	}
}

void remove_Single_Item(Song *&ptrArray)
{
	delete[]ptrArray;
	ptrArray = NULL;
}

void remove_All(Song *ptrArray[], int count)
{
	for (int i = 0; i < count; i++)
	{
		if (ptrArray[i] != NULL)
		{
			delete[]ptrArray[i];
		}
	}
	delete[] ptrArray;
}
void Reset(Song *ptrArray[], int &count)
{
	// Finding The Index Where It Will Find NULL because When I
	// remove Any Item then I have assigned it to NULL.... 
	int store = 0;
	for (int i = 0; i < count; i++)
	{
		if (ptrArray[i] == NULL)
		{
			store = i;
		}
	}

	// Will Reset All The Items In Order To Fill Up The Space.....
	for (int i = store; i < count - 1; i++)
	{
		ptrArray[i] = ptrArray[i + 1];

	}
	ptrArray[count - 1] = NULL;
	count--;

}
