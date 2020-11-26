﻿#include <iostream>
#include <vector>
using namespace std;

//construct tree, print postorder
//主要留意construct tree果度嘅recursion

int preIndex = 0; // index of current root

class Node
{
public:
	int data;
	Node* left;
	Node* right;
	Node(int d) : data(d), left(NULL), right(NULL)
	{
	}
};

class Tree
{
public:
	Node* root;

	int search(vector<int> in, int target, int start, int end) // find index of given data in inorder array
	{
		for (int i = start; i <= end; i++)
			if (in[i] == target)
				return i;
	}

	Node* disperse(vector<int> pre, vector<int> in, int inStart, int inEnd)
	{
		// pre: 1 2 4 5 3             1 2 3
		// in : 4 2 5 1 3             2 1 3
		if (inStart > inEnd)
			return NULL;

		Node* temp = new Node(pre[preIndex++]);
		if (inStart == inEnd) // no child
			return temp;

		int inIndex = search(in, temp->data, inStart, inEnd);
		temp->left = disperse(pre, in, inStart, inIndex - 1); // construct left tree
		temp->right = disperse(pre, in, inIndex + 1, inEnd); // construct right tree

		return temp;
	}

	void printPostorder(Node* n)
	{
		if (n == NULL)
			return;
		printPostorder(n->left);
		printPostorder(n->right);
		cout << n->data;

		(n == root) ? cout << endl : cout << " ";
	}
};

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int N;
		cin >> N;

		int temp;
		vector<int> pre, in;
		for (int i = 0; i < N; i++)
		{
			cin >> temp;
			pre.push_back(temp);
		}

		for (int i = 0; i < N; i++)
		{
			cin >> temp;
			in.push_back(temp);
		}

		Tree* tree = new Tree();
		tree->root = tree->disperse(pre, in, 0, N - 1);
		tree->printPostorder(tree->root);

		preIndex = 0; // reset
	}

	return 0;
}