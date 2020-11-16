#include <iostream>
#include <vector>
using namespace std;

//首先construct tree
//跟住將root去目標嘅所有node data記錄係vector度
//一共有2條
//例如題目中嘅tree就會整到以下2個vector
//path1 = {6,8,3,7}
//path2 = {12,3,7}
//從vector中最尾遍歷到最頭，如果佢地唔一樣，eg 8 ！= 12，咁翻轉頭1個 (3) 就係佢地嘅closest ancestor
//ouput 3，完

vector<int> path1, path2; // record the node's path

class Node
{
public:
	int data;
	vector<Node*> children;
	Node* parent;

	Node(int d) :data(d), children(NULL), parent(NULL)
	{
	}
};

class Tree
{
public:
	Node* root;

	Node* findNode(int data, Node *n)
	{
		if (n->data == data)
			return n;
		else
		{
			for (Node *child : n->children)
			{
				Node *result = findNode(data, child);
				if (result != NULL)
					return result;
			}
		}
		return NULL;
	}

	void addNode(int data, int parentData)
	{
		Node* parent = findNode(parentData, root);
		Node* temp = new Node(data);
		temp->parent = parent;
		parent->children.push_back(temp);
	}

	void setRoot(int data)
	{
		this->root = new Node(data);
	}

	void genArray(int data, bool isPath1)
	{
		Node* target = findNode(data, root);
		while (target->parent != NULL)
		{
			isPath1? path1.push_back(target->data) : path2.push_back(target->data);
			target = target->parent;
		}
		// add the root data finally
		isPath1 ? path1.push_back(root->data) : path2.push_back(root->data);
	}
};

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		Tree* tree = new Tree;
		int rootData, N;
		cin >> rootData >> N;
		tree->setRoot(rootData);

		int self, parent;
		for (int i = 0; i < N - 1; i++)
		{
			cin >> self >> parent;
			tree->addNode(self, parent);
		}

		int target1, target2;
		cin >> target1 >> target2;
		tree->genArray(target1, true);
		tree->genArray(target2, false);

		//for (int i : path1)
		//	cout << i << " ";
		//cout << endl;
		//for (int j : path2)
		//	cout << j << " ";
		//cout << endl;
		
		vector<int>::iterator it1 = --path1.end(); // get the last it
		vector<int>::iterator it2 = --path2.end();
		while (*it1 == *it2)
		{
			it1--;
			it2--;
		}
		cout << *++it1 << endl;

		path1.clear();
		path2.clear();
	}

	return 0;
}