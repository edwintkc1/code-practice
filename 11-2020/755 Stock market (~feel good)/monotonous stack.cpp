#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define ll long long
using namespace std;

// 單調遞增棧 montontone stack
// https://www.youtube.com/watch?v=GYuBQacXr1A 
// leetcode 84

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int N, temp;
		cin >> N;
		vector<ll> stocks;
		for (int i = 0; i < N; i++) // input
		{
			cin >> temp;
			stocks.push_back(temp);
		}

		stack<ll> stack;
		stack.push(-1);
		ll maxValue = 0;
		for (int i = 0; i < N; i++)
		{
			while (stack.top() != -1 && stocks[stack.top()] >= stocks[i])
			{
				ll temp = stocks[stack.top()];
				stack.pop();
				temp *= (i - stack.top() - 1);
				maxValue = max(maxValue, temp);
			}

			stack.push(i);

		}
		while (stack.top() != -1)
		{
			ll temp = stocks[stack.top()];
			stack.pop();
			temp *= (stocks.size() - stack.top() - 1);
			maxValue = max(maxValue, temp);
		}
		cout << maxValue << endl;

	}

	return 0;
}
