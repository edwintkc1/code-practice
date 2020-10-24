#include <iostream>
#include <vector>
using namespace std;

class coordinate
{
public:
	int x;
	int y;

	coordinate() : x(0), y(0)
	{
	}

	coordinate(int X, int Y) :x(X), y(Y)
	{
	}

	bool operator==(coordinate& point)
	{
		if (this->x == point.x && this->y == point.y)
			return true;
		return false;
	}
};


coordinate start(9999, 9999); // return stuff for findStartPoint()
coordinate& findStartPoint(vector<coordinate>& list)
{
	int listSize = list.size();
	for (int i = 0; i < listSize; i++)
	{
		if (list[i].y < start.y)
			start = list[i];
		else if (list[i].y == start.y) // if 2 pts have same y, choose samller the one with smaller x
			if (list[i].x < start.x)
				start = list[i];
	}
	return start;
}

int crossProduct(coordinate a, coordinate b, coordinate c)
{
	double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (area < 0) // clockwise direction
		return -1;
	else if (area > 0)
		return 1; // counter clockwise direction (we need this since start point is bottomleftMost)
	return 0; // collinear
}

int main()
{
	int K;
	cin >> K;
	int uselessK = K;
	while (K--)
	{
		int N;
		cin >> N;
		if (N == -1) // useless 
		{
			K++;    //add one more to make up for the K--
			continue;
		}

		vector<coordinate> list;
		vector<coordinate> ans;
		while (N--)
		{
			int x, y;
			cin >> x >> y;
			list.push_back(coordinate(x,y));
		}
		cout << -1 << endl;
		//if (uselessK == (K + 1))
		//	cout << uselessK << endl;

		coordinate startPoint = findStartPoint(list); // find the first point
		coordinate previous = startPoint;
		ans.push_back(previous);

		int index = 0;
		while (1)
		{
			if (index >= list.size()) // means traverse all points already, break
				break;


			coordinate next = list[index++];
			if (next == previous || next == startPoint)
				continue;


			bool allPointCounterClockWise = true;
			for (int i = 0; i < list.size(); i++)
			{
				if (!allPointCounterClockWise)
					break;
				//if (next == previous) // skip this point, because 3 points only form 1 line
				//	continue;
				int direction = crossProduct(previous, next, list[i]); // 1 = counterClockWise
				// if all line (next-list[i]) reagrading the line (previous-next) is counterClockWise
				// that is the point we need
				if (direction == -1) // -1 = clockwise, false
					allPointCounterClockWise = false;
			}

			if (allPointCounterClockWise == true)
			{
				previous = next;
				ans.push_back(previous);
				index = 0;
			}
		}

		ans.push_back(startPoint); // go back to start
		int ansSize = ans.size();

		cout << ansSize << endl;
		for (int i = 0; i < ansSize; i++)
			cout << ans[i].x << " " << ans[i].y << endl;
	}
	return 0;
}


//1
//15
//30 30
//250 50
//50 60
//60 20
//70 45
//86 39
//112 60
//200 113
//300 200
//130 240
//76 150
//47 76
//36 40
//33 35
//30 30

