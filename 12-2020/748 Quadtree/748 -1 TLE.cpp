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

int count(vector<string>& graph, int x, int y, int size) {
	if (size == 1)
		return 1;

	int newSize = size / 2;
	if (newSize == 1) // if newSize = 1, oldSize = 2 = the graph now is 2x2, send in compare 4 boxes
	{
		if (compare(graph, newSize, x, y) == true)
			return 1;
		else
			return 5;
	}
	else // keep dividing the graph into 4 small pieces
	{
		int sum = 0;

		int topLeft = count(graph, x, y, newSize);
		int topRight = count(graph, x + newSize, y, newSize);
		int bottomLeft = count(graph, x, y + newSize, newSize);
		int bottomRight = count(graph, x + newSize, y + newSize, newSize);

		if (topLeft == 1 && topRight == 1 && bottomLeft == 1 && bottomRight == 1 && compare(graph, newSize, x, y))
			sum = 1; // all 4 areas are same
		else // not same
			sum = topLeft + topRight + bottomLeft + bottomRight;

		if (sum != 1) // if all 4 areas are not same
			sum += 1; // add the root

		return sum;
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int k;
		cin >> k;
		int n = 1;
		n = n << k; // n = 2^k

		vector<string> graph;
		string line;
		int graphIndex = 0;
		for (int i = 0; i < n; i++) // input
		{
			cin >> line;
			graph.push_back(line);
		}

		int m, row, col;
		cin >> m;
		for (int i = 0; i < m; i++)  // flip and give output
		{
			cin >> row >> col;
			if (graph[row - 1][col - 1] == '0')
				graph[row - 1][col - 1] = '1';
			else
				graph[row - 1][col - 1] = '0';
			std::cout << count(graph, 0, 0, n) << endl;
		}
	}
	return 0;
}