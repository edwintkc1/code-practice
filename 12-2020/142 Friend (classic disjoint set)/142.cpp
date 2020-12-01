#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//經典disjoint set題目
//首先有幾多人就create幾多nodes，每個node 有initial parent = 自己，size = 1
//*一開始每個node都係一個tree
//之後會執行merge (根據size，size較小者融合到size較大者)
//期間會call find()，順便將tree 變flat (直接將自己point去tree嘅root)，以減少search嘅時間
//最尾search曬所有node，搵出最大嘅size，完

class node
{
public:
	int parent, size;

	node(int p, int s) :parent(p), size(s)
	{
	}

	static int find(vector<node> &set, int i) // find set's root, do path compression also
	{
		if (set[i].parent == i)
			return i;
		else
		{
			set[i].parent = find(set, set[i].parent);
			return set[i].parent;
		}
	}

	static void merge(vector<node>& set, int a, int b)
	{
		int a_parent = find(set, a);
		int b_parent = find(set, b);
		if (a_parent == b_parent) // already in same set
			return;
		else if (set[a_parent].size > set[b_parent].size) // set A > set B
		{
			set[b_parent].parent = a_parent; // merge B to A
			set[a_parent].size += set[b_parent].size;
		}
		else if (set[a_parent].size < set[b_parent].size) // set A < set B 
		{
			set[a_parent].parent = b_parent; // merge A to B
			set[b_parent].size += set[a_parent].size;
		}
		else // set A = set B
		{
			set[a_parent].parent = b_parent; // merge A to B / merge B to A , here choose the first one
			set[b_parent].size += set[a_parent].size;
		}
	}
};

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int numOfppl, numOfpairs;
		cin >> numOfppl >> numOfpairs;

		vector<node> set;
		for (int i = 0; i <= numOfppl; i++)
		{
			node n(i,1); // node initial parent is itself, size = 1
			set.push_back(n);
		}

		int a, b;
		for (int i = 0; i < numOfpairs; i++)
		{
			cin >> a >> b;
			node::merge(set, a, b);
		}

		int m = 0;
		for (int i = 0; i <= numOfppl; i++)
			m = max(set[i].size, m);

		cout << m << endl;
	}
	return 0;
}