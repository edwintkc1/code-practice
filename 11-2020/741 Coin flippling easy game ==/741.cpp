#include <iostream>
#include <string>
using namespace std;

//試想想，如果col係fixed，咁我地只需要考慮每一個row反唔反，簡單好多
//
//->先將col反轉，然後再試果個情況下嘅 最好反row嘅可能性
//Col 總共有2 ^ 9 可能性，因為每一個都有反同唔反呢2個probi，而係果個情況下，再check曬所有點去決定row反唔反，要9N

//每一個可能性 - 》得出最好嘅row

int countRow(char** coins, int row, int col)
{
	int cnt = 0;
	for (int i = 0; i < row; i++)
	{
		int rowSum = 0;
		for (int j = 0; j < col; j++)
			if (coins[i][j] == '1')
				++rowSum;
		if (rowSum < col / 2)
			rowSum = col - rowSum;
		cnt += rowSum;
	}
	return cnt;
}

int countCol(char** coins, int row, int col)
{
	int cnt = 0;
	for (int i = 0; i < col; i++)
	{
		int colSum = 0;
		for (int j = 0; j < row; j++)
			if (coins[i][j] == '1')
				++colSum;
		if (colSum < col / 2)
			colSum = col - colSum;
		cnt += colSum;
	}
	return cnt;
}

void flipRow(char** coins, int row, int col, int lineNumber)
{
	for (int i = 0; i < col; i++)
	{
		if (coins[lineNumber][i] == '0')
			coins[lineNumber][i] = '1';
		else
			coins[lineNumber][i] = '0';
	}
}

void flipCol(char** coins, int row, int col, int lineNumber)
{
	for (int i = 0; i < row; i++)
	{
		if (coins[i][lineNumber] == '0')
			coins[i][lineNumber] = '1';
		else
			coins[i][lineNumber] = '0';
	}
}

char** genTempCoins(char** coins, int row, int col)
{
	char** temp = new char* [row];
	for (int r = 0; r < row; r++) // initialize and copy
	{
		temp[r] = new char[col];
		for (int c = 0; c < col; c++)
			temp[r][c] = coins[r][c];
	}
	return temp;
}

int tryRow(char** coins, int row, int col)
{
	int sum = 0;

	int totalTimeNeeded = 2 << row;
	for (int i = 0; i < totalTimeNeeded; i++)
	{
		char** temp = genTempCoins(coins, row, col);

		int j = 0;
		while (j < row)
		{
			if (i & (1 << j))
				flipRow(temp, row, col, j);
			j++;
		}

		int tempSum = countCol(temp, row, col);
		if (tempSum > sum)
			sum = tempSum;

	}
	return sum;
}

int tryCol(char** coins, int row, int col)
{
	int sum = 0;

	int totalTimeNeeded = 2 << col;
	for (int i = 0; i < totalTimeNeeded; i++)
	{

		char** temp = genTempCoins(coins, row, col);

		int j = 0;
		while (j < col)
		{
			if (i & (1 << j))
				flipCol(temp, row, col, j);
			j++;
		}

		int tempSum = countRow(temp, row, col);
		if (tempSum > sum)
			sum = tempSum;

	}
	return sum;
}

int main()
{
	int row, col;
	while (cin >> row >> col)
	{
		char** coins = new char* [row]; // initialize coins
		for (int i = 0; i < row; i++)
			coins[i] = new char[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				cin >> coins[i][j];

		int ans = 0;
		if (col < row)
			ans = tryCol(coins, row, col); // try all posibility 
		else
			ans = tryRow(coins, row, col);

		cout << ans << endl;

	}

	return 0;
}