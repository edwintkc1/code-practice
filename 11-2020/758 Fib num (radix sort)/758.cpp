#include <iostream>
#include <vector>
#include <algorithm>
#define mask 1023
#define ll long long
using namespace std;

// 第一次用base 10，with 10 buckets做，TLE
// tutor: 用radix sort base 2 (1024) 做，會快d
// 遂用1024
// 收穫n次TLE後，改用bitwise mudulo提升速度
// bitwise modulo: %2 = &1,  %8 = &7,  %1024 = &1023
// 再n次後MLE後，發現要delete array釋放空間
// 又數次後runtime error後，發現fib呢個array delete唔到
// 因為fib申請左n個空間，照計只可以從0寫到<n 
// 但我最後一個位都寫埋，overflow
// delete左唔屬於自己嘅memory，所以runtime error
// -> 將fib array 空間 set高少少

void countSort(ll* vec, int n, int div)
{
	ll* output = new ll[n];
	int count[1024] = { 0 };

	for (int i = 0; i < n; i++) // store occurance
		count[(vec[i] >> (div * 10)) & mask]++;

	for (int i = 1; i < 1024; i++) // cumulative add
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--) // sort
	{
		output[count[(vec[i] >> (div * 10)) & mask] - 1] = vec[i];
		count[(vec[i] >> (div * 10)) & mask]--;
	}

	for (int i = 0; i < n; i++) // assignment
		vec[i] = output[i];

	delete[] output;
	output = NULL;
}

void getAns(int n, int Q)
{
	ll* fib = new ll[n+2];
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i <= n; i++) // generate fib num
		fib[i] = (fib[i - 1] + fib[i - 2]) % Q; // step 1-2

	ll max = 0;
	for (int i = 0; i <= n; i++) // find max for step 3 
		if (fib[i] > max)
			max = fib[i];

	//vector<ull> vec;
	//ull max = 0;
	//for (int i = 1; i <= n; i++) // modulo, put it into new vec (skip F0)
	//{
	//	vec.push_back(fib[i] % Q);
	//	if (vec[i-1] > max) // find max also
	//		max = vec[i-1];
	//}

	int newSize = n + 1;
	for (int div = 0; max >> (div * 10) > 0; div++) // step 3: radix sort
		countSort(fib, newSize, div);

	ll sum = 0;
	for (int i = 1; i <= n; i++) // step 4
		sum += fib[i] * i % Q;
	cout << sum % Q << endl;

	delete[] fib;
	fib = NULL;
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, Q;
		cin >> n >> Q;
		getAns(n, Q);
	}
	return 0;
}