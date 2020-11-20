#include <iostream>
#include <string>
using namespace std;

class Stack
{
public:
	int top = -1;
	int arr[10000];

	bool isEmpty() { return (top == -1); }
	void push(int c)
	{
		arr[++top] = c;
	}
	int pop()
	{
		if (!isEmpty())
			return arr[top--];
	}
};

int main()
{
	string input;
	while (getline(cin,input))
	{
		Stack myStack;

		int first, second, temp;
		for (char c : input)
		{
			if (c == ' ')
				continue;
			else if (c >= '0' && c <= '9')
			{
				temp = c - '0';
				myStack.push(temp);
			}
			else if (c == '+')
			{
				first = myStack.pop();
				second = myStack.pop();
				myStack.push(second + first);
			}
			else if (c == '-')
			{
				first = myStack.pop();
				second = myStack.pop();
				myStack.push(second - first);
			}
			else if (c == '*')
			{
				first = myStack.pop();
				second = myStack.pop();
				myStack.push(second * first);
			}
		}
		int ans = myStack.pop();
		cout << ans << endl;
	}

	return 0;
}