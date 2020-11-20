#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int T, round = 1;
	cin >> T;
	while (T--)
	{
		int N;
		cin >> N;
		
		int high = 0, low = 0;
		int now, next;
		cin >> now; // initial height
		for (int i = 0; i < N - 1; i++)
		{
			cin >> next;
			if (now < next)
				high++;
			else if (now > next)
				low++;
			
			now = next;
		}

		cout << "Case " << round++ << ": " << high << " " << low << endl;
	}

	return 0;
}