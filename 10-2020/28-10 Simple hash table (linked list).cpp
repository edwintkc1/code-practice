#include <iostream>
#include <list>
using namespace std;

class Hash
{
	int size;
	list<int>* table;
public:
	Hash(int size)
	{
		this->size = size;
		table = new list<int>[size];
	}

	int hashFunction(int x)
	{
		return (x % size);
	}

	void insertItem(int x)
	{
		int index = hashFunction(x);
		table[index].push_back(x);
	}

	void deleteItem(int x)
	{
		int index = hashFunction(x);
		
		list<int>::iterator it = table[index].begin();
		for (; it != table[index].end(); it++)
			if (*it == x)
				break;

		if (it != table[index].end()) // means found
			table[index].erase(it);
	}

	void display()
	{
		for (int i = 0; i < size; i++)
		{
			cout << i;
			for (auto j : table[i])
				cout << "--> " << j;
			cout << endl;
		}
		cout << "----------------------------------" << endl;
	}
};

int main()
{
	int a[] = { 15, 11, 27, 8 , 12, 22 };
	int size = sizeof(a) / sizeof(a[0]);

	Hash h(7);

	for (int i = 0; i < size; i++)
		h.insertItem(a[i]);

	h.display();

	h.deleteItem(12);
	h.deleteItem(22);

	h.display();
	return 0;
}