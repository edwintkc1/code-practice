#include <iostream>
#include <vector>
#include <string>
using namespace std;

//第一次:flip完重新做recursion計nodes，TLE
//tutor:因為有好多case flip完都無改變
//可以只做改變嘅部分，減少時間
//下面分開4個部分做 (topLeft, topRight, bottomLeft, bottomRight)
//每個部分又分 flip完後有改變/無改變
//無變直接return original value
//有變就再分純色/不純

class node {
public:
	int size, layer;
	char pixel, nodedata;
	node* topLeft, * topRight, * bottomLeft, * bottomRight;

	node(int s, int depth, char p, char n, node* nw, node* ne, node* sw, node* se) :
		size(s), layer(depth), pixel(p), nodedata(n), topLeft(nw), topRight(ne), 
		bottomLeft(sw), bottomRight(se)
	{
	}
	
	// for base node
	node(int s, int newSize, char p, char n) : size(s), layer(newSize), pixel(p), nodedata(n), 
		topLeft(NULL), topRight(NULL), bottomLeft(NULL), bottomRight(NULL)
	{
	}

	void clear(node* n)
	{
		if (n == NULL) {
			return;
		}
		clear(n->topLeft);
		clear(n->topRight);
		clear(n->bottomLeft);
		clear(n->bottomRight);
		delete n;
	}
};

//	node* tree = newquadtree(0, n - 1, 0, n - 1);
node* genTree(char**graph, int start_i, int end_i, int start_j, int end_j) {
	char pixel = graph[start_i][start_j];

	int size = end_i - start_i + 1;
	if (size == 1)
		return new node(1, size, pixel, pixel);

	int newSize = size / 2 - 1;
	node* topLeft = genTree(graph, start_i, start_i + newSize, start_j, start_j + newSize);
	node* topRight = genTree(graph, start_i + size / 2, end_i, start_j, start_j + newSize);
	node* bottomLeft = genTree(graph, start_i + size / 2, end_i, start_j + size / 2, end_j);
	node* bottomRight = genTree(graph, start_i, start_i + newSize, start_j + size / 2, end_j);

	bool isSame = topLeft->nodedata == topRight->nodedata && 
		topLeft->nodedata == bottomRight->nodedata &&
		bottomLeft->nodedata == bottomRight->nodedata;

	// -1 = current box contain black and white
	bool notCotainBoth = topLeft->nodedata != '2' && topLeft->nodedata == pixel;
	int notSameSize = topLeft->size + topRight->size + bottomRight->size + bottomLeft->size + 1;

	if (isSame && notCotainBoth)
		return new node(1, size, pixel, pixel, topLeft, topRight, bottomRight, bottomLeft);
	else
		return new node(notSameSize, size, pixel, '2', topLeft, topRight, bottomRight, bottomLeft);
}

node* flip(char** graph, node* original, int start_i, int end_i, int start_j, int end_j, int row, int col) {
	char pixel = graph[start_i][start_j];
	int size = end_i - start_i + 1;
	int newSize = size / 2 - 1;

	node* temp;
	if (size == 1)
		return new node(1, size, pixel, pixel);
	else {
		bool isSame = original->topLeft->nodedata == original->topRight->nodedata &&
			original->topLeft->nodedata == original->bottomRight->nodedata &&
			original->bottomLeft->nodedata == original->bottomRight->nodedata;

		if (start_i <= row && row <= start_i + newSize) // left half
		{
			if (start_j <= col && col <= start_j + newSize) // top left
			{
				// temp = temp topLeft
				temp = flip(graph, original->topLeft, start_i, start_i + newSize, start_j, start_j + newSize, row, col);

				bool tempIsSame = temp->nodedata == original->topRight->nodedata &&
					original->topRight->nodedata == original->bottomLeft->nodedata &&
					original->bottomLeft->nodedata == original->bottomRight->nodedata;

				int notSame_size = temp->size + original->topRight->size + original->bottomLeft->size + original->bottomRight->size + 1;
				if (isSame && tempIsSame)
				{
					if (original->nodedata == '2') // this box contains both black and white
						// return new size = add all the nodes's size + 1
						return new node(notSame_size, size, pixel, original->nodedata, temp, original->topRight, original->bottomLeft, original->bottomRight);
					// contain black/white only
					return new node(1, size, pixel, original->nodedata, temp, original->topRight, original->bottomLeft, original->bottomRight);
				}
				else // not same
				{
					if (original->nodedata == '2') 
					{
						if (tempIsSame && temp->nodedata != '2')
							return new node(1, size, pixel, temp->nodedata, temp, original->topRight, original->bottomLeft, original->bottomRight);
						return new node(notSame_size, size, pixel, '2', temp, original->topRight, original->bottomLeft, original->bottomRight);
					}
					return new node(notSame_size, size, pixel, '2', temp, original->topRight, original->bottomLeft, original->bottomRight);
				}
			} 
			else // bottom left
			{
				// temp = temp bottomLeft
				temp = flip(graph, original->bottomLeft, start_i, start_i + newSize, start_j + size / 2, end_j, row, col);

				bool tempIsSame = original->topLeft->nodedata == original->topRight->nodedata && 
					original->topRight->nodedata == temp->nodedata && 
					temp->nodedata == original->bottomRight->nodedata;

				int notSame_size = original->topLeft->size + original->topRight->size + temp->size + original->bottomRight->size + 1;
				if (isSame && tempIsSame)
				{
					if (original->nodedata == '2') // same as above , not same return all node's size + 1
						// only the bottom left changes
						return new node(notSame_size, size, pixel, original->nodedata, original->topLeft, original->topRight, temp, original->bottomRight);
					return new node(1, size, pixel, original->nodedata, original->topLeft, original->topRight, temp, original->bottomRight);
				}
				else {
					if (original->nodedata == '2')
					{
						if (tempIsSame && temp->nodedata != '2')
							return new node(1, size, pixel, graph[row][col], original->topLeft, original->topRight, temp, original->bottomRight);
						return new node(notSame_size, size, pixel, '2', original->topLeft, original->topRight, temp, original->bottomRight);
					}
					return new node(notSame_size, size, pixel, '2', original->topLeft, original->topRight, temp, original->bottomRight);
				}
			}
		} // end of left half
		else // right half
		{
			if (start_j <= col && col <= start_j + newSize) // top right
			{
				// temp = temp topRight
				temp = flip(graph, original->topRight, start_i + size / 2, end_i, start_j, start_j + newSize, row, col);;

				bool tempIsSame = original->topLeft->nodedata == temp->nodedata && 
					temp->nodedata == original->bottomLeft->nodedata && 
					original->bottomLeft->nodedata == original->bottomRight->nodedata;

				int notSame_size = original->topLeft->size + temp->size + original->bottomLeft->size + original->bottomRight->size + 1;
				if (isSame && tempIsSame)
				{
					if (original->nodedata == '2')// same as above , not same return all node's size + 1
						// only the top right changes
						return new node(notSame_size, size, pixel, original->nodedata, original->topLeft, temp, original->bottomLeft, original->bottomRight);
					return new node(1, size, pixel, original->nodedata, original->topLeft, temp, original->bottomLeft, original->bottomRight);
				}
				else {
					if (original->nodedata == '2')
					{
						if (tempIsSame && temp->nodedata != '2')
							return new node(1, size, pixel, graph[row][col], original->topLeft, temp, original->bottomLeft, original->bottomRight);
						return new node(notSame_size, size, pixel, '2', original->topLeft, temp, original->bottomLeft, original->bottomRight);
					}
					return new node(notSame_size, size, pixel, '2', original->topLeft, temp, original->bottomLeft, original->bottomRight);
				}
			}
			else // bottom right
			{
				// temp = temp bottomRight
				temp = flip(graph, original->bottomRight, start_i + size / 2, end_i, start_j + size / 2, end_j, row, col);

				bool tempIsSame = original->topLeft->nodedata == original->topRight->nodedata && 
					original->topRight->nodedata == original->bottomLeft->nodedata && 
					original->bottomLeft->nodedata == temp->nodedata;

				int notSame_size = original->topLeft->size + original->topRight->size + original->bottomLeft->size + temp->size + 1;
				if (isSame && tempIsSame)
				{
					if (original->nodedata == '2')
						return new node(notSame_size, size, pixel, original->nodedata, original->topLeft, original->topRight, original->bottomLeft, temp);
					return new node(1, size, pixel, original->nodedata, original->topLeft, original->topRight, original->bottomLeft, temp);
				}
				else 
				{
					if (original->nodedata == '2') 
					{
						if (tempIsSame && temp->nodedata != '2')
							return new node(1, size, pixel, graph[row][col], original->topLeft, original->topRight, original->bottomLeft, temp);
						return new node(1 + temp->size + original->bottomLeft->size + original->topLeft->size + original->topRight->size, size, pixel, '2', original->topLeft, original->topRight, original->bottomLeft, temp);
					}
					return new node(notSame_size, size, pixel, '2', original->topLeft, original->topRight, original->bottomLeft, temp);
				}
			}
		} // end of right half
	}
}

int main() {
	int T;
	cin >> T;
	while(T--){
		int k;
		cin >> k;
		int n = 1 << k;  // n = 2^k

		char** graph = new char* [n+5];
		for (int i = 0; i < n; i++) //initialize graph
			graph[i] = new char[n+5];

		for (int i = 0; i < n; i++)
			cin >> graph[i];
		
		int m;
		cin >> m;

		int row, col;
		node* tree = genTree(graph, 0, n - 1, 0, n - 1);
		for (int i = 0; i < m; i++) {
			cin >> row >> col;
			--row, --col;  // for actual row, col index

			if (graph[row][col] == '0') // flip
				graph[row][col] = '1';
			else
				graph[row][col] = '0';

			tree = flip(graph, tree, 0, n - 1, 0, n - 1, row, col); // update tree

			cout << tree->size << endl;
		}
		tree->clear(tree);
		for (int i = 0; i < n; i++)
			delete graph[i];
		delete[] graph;
		graph = NULL;
	}
}