#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

//當2個queue都有野，就要根據翻宜家嘅時間做野
//如果2個queue入面第一個task嘅arriveTime都 > 宜家嘅時間
//證明佢地都未到，咁我地攞近d果個
//else if 其中一個queue嘅第一個task.arriveTime > 宜家嘅時間
//搞佢 (留意判斷high queue先)
//
//上面loop完後，應該得翻一個queue有野
//整曬佢，搞掂

class Task
{
public:
	int arriveTime, processTime, priority, index; // index is for sorting the answer queue
	int finishTime; // for the ans
	Task(int arrive, int process, int prior, int i) : arriveTime(arrive), processTime(process),
		priority(prior), index(i)
	{
	}

};

int main()
{
	int n;
	while (cin >> n)
	{
		queue<Task> low, high;
		int arriveTime, processTime, priority; // priority = 0 means higher
		for (int i = 0; i < n; i++) // input
		{
			cin >> arriveTime >> processTime >> priority;
			Task subTask(arriveTime, processTime, priority, i);

			if (priority == 0)
				high.push(subTask);
			else
				low.push(subTask);
		}

		int time = 0;
		vector<Task> ans;

		while (!high.empty() && !low.empty()) // both not empty
		{  // both not yet arrived, simply take the faster one
			if (high.front().arriveTime > time && low.front().arriveTime > time)
				time = min(high.front().arriveTime, low.front().arriveTime);
			if (time >= high.front().arriveTime)
			{ // high.front() is waiting, do it first
				time += high.front().processTime;
				high.front().finishTime = time;
				ans.push_back(high.front());
				high.pop();
			}
			else
			{ // low.front() is waiting and high.front() is not yet arrived, do low.front()
				time += low.front().processTime;
				low.front().finishTime = time;
				ans.push_back(low.front());
				low.pop();
			}

		}
		// after finish the above step, one of the queue should be empty
		// simply do all the task in the NOT empty queue
		while (!high.empty())
		{
			time = max(time, high.front().arriveTime);
			time += high.front().processTime;
			high.front().finishTime = time;
			ans.push_back(high.front());
			high.pop();
		}
		while (!low.empty())
		{
			time = max(time, low.front().arriveTime);
			time += low.front().processTime;
			low.front().finishTime = time;
			ans.push_back(low.front());
			low.pop();
		}

		sort(ans.begin(), ans.end(), [](const Task& task1, const Task& task2)
			{
				return task1.index < task2.index;
			});

		for (int i = 0; i < n; i++) {
			cout << ans[i].finishTime;
			if (i != n - 1)
				cout << " ";
		}
		cout << endl;

	}

	return 0;
}