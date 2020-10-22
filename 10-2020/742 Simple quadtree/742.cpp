#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool compare(vector<string>& graph, int size, int x, int y)
{
	if ((graph[x][y] == graph[x + size][y]) && (graph[x][y + size] == graph[x + size][y + size])
		&& (graph[x][y] == graph[x + size][y + size]))
		return true; // top left == top right == bottom left == bottom right
	return false;
}

int count(vector<string>& graph, int size, int x, int y)
{

	int newSize = size / 2;
	if (newSize == 1) // now the graph is 2x2, send in compare 4 boxes
	{
		if (compare(graph, newSize, x, y) == true)
			return 1;
		return 5;
	}
	else // keep dividing the graph into 4 small pieces
	{
		int sum = 0;
		int topLeft = count(graph, newSize, x, y);
		int topRight = count(graph, newSize, x + newSize, y);
		int bottomLeft = count(graph, newSize, x, y + newSize);
		int bottomRight = count(graph, newSize, x + newSize, y + newSize);

		if (((topLeft == topRight == bottomLeft == bottomRight) == 1))
			sum = 1;
		else
			sum = topLeft + topRight + bottomLeft + bottomRight;

		if (sum != 1) // if all same no need to + 1
			sum++; // root 
		return sum;
	}
}


int main()
{
	int k;
	while (cin >> k)
	{
		int n = 1;
		n = n << k;  // power

		vector<string> graph;
		graph.resize(n);

		string line;
		int graphIndex = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> line;
			graph[graphIndex++] = line;
		}

		int ret = count(graph, n, 0, 0);
		cout << ret << endl;
	}

	return 0;
}