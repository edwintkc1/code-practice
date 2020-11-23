#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

//brute froce, 先定點，左右開始掃過去x (step) 步
//每次睇下邊個最細，用min*step，++step
//直到果個點試曬所有step乘min得嘅tempMax
//換下一個點，重複以上步驟
//使曬所有點=試曬所有可能性，得出max

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

		ll max = 0;
		for (int i = 0; i < N; i++)
		{
			ll minValue = INT64_MAX;
			for (int step = 0; step <= N; step++)
			{
				for (int j = i; j < step && j <= N; j++)
					minValue = min(minValue, stocks[j]);
				for (int j = i; j > i - step && j >= 0; j--)
					minValue = min(minValue, stocks[j]);

				ll tempMax = minValue * step;
				if (tempMax > max)
					max = tempMax;
			}
		}
		cout << max << endl;

	}

	return 0;
}
