#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//揀個mid先，假設mid嘅distance係tempMax 
//從所有rooms最左邊loop到最右，當dis大於等於tempMax，擺個人入去
//如果最後可以擺曬，證明宜家嘅realMax >= tempMax
//仲可以將距離加大。 反之亦然
//跟住就binary serach，直到搵到答案
//https://blog.csdn.net/xrr233/article/details/106999537 

int binarySearch(int mid, int ppl, int left, int right, vector<int>& rooms)
{
	if (left > right)
		return mid;
	int midValue = (left + right) >> 1;

	int count = 1, now = rooms[0];
	// initially count = 1, as the first room must be occupied
	for (int i = 0; i < rooms.size(); i++)
	{
		if (rooms[i] - now >= midValue)
		{
			++count;
			now = rooms[i];
		}
	}

	if (count >= ppl)
		return binarySearch(midValue, ppl, midValue + 1, right, rooms);
	else
		return binarySearch(mid, ppl, left, midValue - 1, rooms);
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int N, C;
		cin >> N >> C;
		vector<int> rooms;
		for (int i = 0; i < N; i++)
		{
			int temp = 0;
			cin >> temp;
			rooms.push_back(temp);
		}

		sort(rooms.begin(), rooms.end());

		int ans = binarySearch(12345, C, 0, rooms.back()-rooms[0], rooms);
		cout << ans << endl;
	}

	return 0;
}
