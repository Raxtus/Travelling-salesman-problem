#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
using namespace std;

int n;
double cDistance, shortestDistance;
struct POINT
{
	double x, y;
};
POINT *label;
POINT *shortestLabel;
size_t pointer=0;

class VECTOR
{
public:

	size_t begin;
	size_t end;
	double distance;

	VECTOR()
	{
		begin = pointer;
		pointer++;
		end = pointer % n;
	}
	double count()
	{
		distance = sqrt(pow((label[end].x - label[begin].x), 2) + pow((label[end].y - label[begin].x), 2));
		return distance;
	}
};
VECTOR *path;

void evolve()
{
	static POINT buf;
	static int pos1, pos2;
	pos1 = rand() % n;
	do
	{
		pos2 = rand() % n;
	} while (pos1 == pos2);

	buf.x = label[pos1].x;
	buf.y = label[pos1].y;
	label[pos1].x = label[pos2].x;
	label[pos1].y = label[pos2].y;
	label[pos2].x = buf.x;
	label[pos2].y = buf.y;

}

int main(int argc, char* argv[])
{
	const unsigned int maxIteration = 10000;
	const unsigned int maxIterationWhithoutProgress = 1000;
	srand(time(NULL));
	fstream file;
	file.open("data.txt", ios::in);
	if (!file.good()) return -1;
	file >> n;
	label = new POINT[n];
	shortestLabel = new POINT[n];
	for (int i = 0; i < n; i++)
	{
		file >> label[i].x;
		file >> label[i].y;
	}
	path = new VECTOR[n];

	for (int i = 0; i < n; i++) path[i].count();
	shortestDistance = 0;
	for (int i = 0; i < n; i++) shortestDistance += path[i].distance;
	for (int i = 0; i < n; i++)
	{
		shortestLabel[i].x = label[i].x;
		shortestLabel[i].y = label[i].y;
	}

	int iterations=0,iterationsWithoutProgress=0;
	do
	{
		evolve();
		cDistance = 0;
		for (int i = 0; i < n; i++) cDistance += path[i].count();
		for (int i = 0; i < n; i++) cout << path[i].distance << endl;
		cout << cDistance << endl << endl;
		if (cDistance < shortestDistance)
		{
			shortestDistance = cDistance;
			for (int i = 0; i < n; i++)
			{
				shortestLabel[i].x = label[i].x;
				shortestLabel[i].y = label[i].y;
			}
		}
		iterations++;
		iterationsWithoutProgress++;
	} while (iterations < maxIteration && iterationsWithoutProgress <maxIterationWhithoutProgress );

	cout << shortestDistance <<endl;
}