#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long 

// brute force / monotonous stack
// 此題用brute force
// 先定中間點，跟住左右行x步，並且係呢個area搵出最細嘅val遲d乘sum
// sum就係左右行果陣加vec[index]
// 試vec入面每一個val 嘅每一個step，就=試曬所有可能性
// 得出最大嘅數，同埋佢嘅start index， end index，完

int main()
{
	int n;
	while (cin >> n)
	{
		vector<ll> vec(n);
		for (int i = 0; i < n; i++)
			cin >> vec[i];

		ll max = INT_MIN, startIndex, endIndex;
		for (int i = 0; i < n; i++)
		{
			ll step = 0;

			while (step < n)
			{
				ll sum = 0, minValue = INT_MAX;
				ll currentLeft = i - step, currentRight = i + step;
				if (currentLeft < 0)
					currentLeft = 0;
				if (currentRight > n)
					currentRight = n;

				for (int x = currentLeft; x <= currentRight && x < n; x++) // find min value for multiplication
					if (vec[x] < minValue)
						minValue = vec[x];


				for (int left = i - 1; left >= (i - step) && left >= 0; left--)
					sum += vec[left];

				for (int right = i + 1; right <= (i + step) && right < n; right++)
					sum += vec[right];

				sum += vec[i];  // add self
				sum *= minValue;
				if (sum > max)
				{
					max = sum;
					startIndex = currentLeft;
					endIndex = currentRight;
				}
				step++;
			}
		}

		cout << max << endl;
		startIndex++;
		endIndex++;

		if (endIndex > n)
			endIndex = n;
		cout << startIndex << " " << endIndex << endl;
	}

	return 0;
}