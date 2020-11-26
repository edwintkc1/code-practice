#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

//node 有frequency，set做send入黎嘅data
//同時又有total frequency，之後merge會有用，construct果陣set埋佢 = frequency先
//
//首先加曬所有野入去priority queue (min heap)度, 每次pop兩個最細嘅frequency出黎，分別係node *left, *right
//整一個新node()，而呢個新node嘅totalfrequency就係left, right嘅frequecy嘅和
//一直做 直到heap得翻1個priority queue得翻1個node
//pop佢出黎做tree node
//
//跟住就開始計ans
//用recursion做，base case係當遇到leaf (frequency = totalFrequency)，就用frequency乘len，加到ans
//send 左右children做recursion


class Node
{
public:
	int frequency, totalFrequency;
	Node* left, * right;
	string code;

	Node(int f) :frequency(f), totalFrequency(f), left(NULL), right(NULL), code("")
	{
	}

	//// overload > operator
	//bool operator>(Node& n)
	//{
	//	if (this->totalFrequency > n.totalFrequency)
	//		return true;
	//	return false;
	//}
};

class compare // for min heap
{
public:
	bool operator()(Node* left, Node* right)
	{
		return left->totalFrequency > right->totalFrequency;
	}
};

class Tree
{
public:
	Node* root;
	int size, total; // size == heap size, total = totalFrequency among all nodes
	priority_queue<Node*, vector<Node*>, compare> heap;

	Tree() :root(NULL), size(0), total(0)
	{
	}

	void add(int frequency)
	{
		++size;
		heap.push(new Node(frequency));
	}

	void genTree()
	{
		while (size != 1)
		{
			// take out 2 nodes with least frequency
			Node* left = heap.top();
			heap.pop();
			Node* right = heap.top();
			heap.pop();

			// gen a new node, its totalFrequency = left.fre + right.fre
			int totalFre = left->totalFrequency + right->totalFrequency;
			Node* temp = new Node(0);
			temp->totalFrequency = totalFre;
			temp->left = left;
			temp->right = right;

			// add new node to heap
			heap.push(temp);
			--size;
		}
		// set the root
		root = heap.top();
		heap.pop();
	}

	// generate totalLength of the heap
	void genLen(Node* n, int len)
	{
		if (n->frequency == n->totalFrequency) // meet leaf node
			total += n->frequency * len;
		else // tarverse tree
		{
			genLen(n->left, len + 1);
			genLen(n->right, len + 1);
		}
	}
};

int main()
{
	int n;
	while (cin >> n)
	{
		Tree* heap = new Tree();

		int data;
		for (int i = 0; i < n; i++) // get input
		{
			cin >> data;
			heap->add(data);
		}

		heap->genTree();
		heap->genLen(heap->root, 0);

		cout << heap->total << endl;
	}
	return 0;
}