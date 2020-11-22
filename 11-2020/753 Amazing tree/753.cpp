#include <iostream>
#include <vector>
#include <string>
using namespace std;

void test(string s, int left, int right, vector<int> &vec)
{
	if (left == right - 1)
	{
		vec.push_back(1);
		return;
	}
	int temp = 1, weight = 1, index = left;
	while (temp)
	{
		++index;
		if (s[index] == '(') { ++weight; ++temp; }
		else if (s[index] == ')') { --temp; }
	}

	vec.push_back(weight);
	if (left + 1 < index - 1)
		test(s, left + 1, index - 1, vec);
	else if (index + 1 < right)
		test(s, index + 1, right, vec);
}

int main()
{
	string s;
	while (cin >> s)
	{
		int left = 0;
		int right = s.length() - 1;
		vector<int> vec;
		test(s, left, right, vec);

		vector<int>::iterator it = vec.begin();
		int ans = 0;
		while (it != vec.end())
		{
			ans ^= *it;
			++it;
		}

		cout << ans << endl;
	}

	return 0;
}
