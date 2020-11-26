#include <iostream>
#include <vector>
using namespace std;

class Heap
{
public:
	int nodes[100005];
	int size, sum;

	Heap() 
	{
		size = 0, sum = 0;
	}

	void insert(int key)
	{
		sum += key;
		int i = size;
		nodes[i] = key;

		while (nodes[i] > nodes[(i - 1) >> 1] && i != 0) // float
		{
			swap(nodes[i], nodes[(i - 1) >> 1]);
			i = (i - 1) >> 1;
		}
		size++;
	}

	void pop()
	{
		sum -= nodes[0];
		nodes[0] = nodes[size - 1];
		nodes[size - 1] = 0;
		int i = 0;
		// sink, (leftchild > me && leftchild not out of size ) || rightchild > me && ...
		while ((nodes[i * 2 + 1] > nodes[i] && i * 2 + 1 < size)
			|| (nodes[i * 2 + 2] > nodes[i] && i * 2 + 2 < size))
		{
			int temp = nodes[i];
			// left > right || right == size (no right child)
			if (nodes[i * 2 + 1] > nodes[i * 2 + 2] || i * 2 + 2 == size)
			{
				nodes[i] = nodes[i * 2 + 1];
				i = i * 2 + 1;
			}
			else
			{
				nodes[i] = nodes[i * 2 + 2];
				i = i * 2 + 2;
			}
			nodes[i] = temp;
		}
	}
};

int main()
{
	int n;
	while (cin >> n)
	{
		Heap *heap = new Heap();

		char op;
		for (int i = 0; i < n; i++)
		{
			int temp = 0;
			cin >> op;
			switch (op)
			{
			case 'a':
				cin >> temp;
				heap->insert(temp);
				break;
			case 'p':
				heap->pop();
				break;
			case 'r':
				cout<< heap->sum << endl;
				break;
			default:
				break;
			}
		}
	}

	return 0;
}