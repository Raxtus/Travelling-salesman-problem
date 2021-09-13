#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <climits>

using namespace std;

size_t n;
double cDistance, shortestDistance;
struct POINT
{
	double x, y;
};
POINT *label;

class GRAPH
{
	static size_t pointer;
public:	

	double translation;
	size_t begin;
	size_t end;

	GRAPH()
	{
		begin = pointer;
		pointer = pointer++%n;
		end = pointer;
		translation = 0;
		count();
		shortestDistance = cDistance;
	}
	void count()
	{
		cDistance -= translation;
		translation = sqrt((label[end].x - label[begin].x, 2) + pow(label[end].y - label[begin].y, 2));
		cDistance += translation;
	}	
};
size_t GRAPH::pointer = 0;

GRAPH *path;
POINT *shortestLabel;
	
void swap(POINT &a, POINT &b)
{
	POINT buff;
	buff = a;
	a = b;
	b = buff;
}
void permute()
{
	size_t V1, V2;
	V1 = rand() % n;
	do V2 = rand() % n; while (V2 == V1);
	swap(label[V1], label[V2]);
	path[V1].count();
	path[V2].count();
	return;
}
bool check()
{
	return cDistance < shortestDistance;
}

int main(int argc, char* argv[])
{
	const unsigned int maxIteration = 10000;
	const unsigned int maxIterationWhithoutProgress = 1000;
	srand(time(NULL));

	fstream file;
	file.open("data.txt", ios::in);
	file >> n;
	label = new POINT[n];
	shortestLabel = new POINT[n];
	for (size_t i = 0; i < n; i++)
	{
		file >> label[i].x >> label[i].y;
	}
	file.close();

	path = new GRAPH[n];	
	for (size_t i = 0; i < n; i++)
	{
		cout << label[i].x << "  "<< label[i].y << endl;
	}

	unsigned int iterationsWithoutProgress = 0;
	for (int i = 0; i < maxIteration && iterationsWithoutProgress < maxIterationWhithoutProgress; i++)
	{
		permute();
		
		if (cDistance < shortestDistance)
		{
			shortestDistance = cDistance;
			memcpy(shortestLabel, label, sizeof(label));
			iterationsWithoutProgress = 0;
			cout << endl << shortestDistance << endl;
		}
		else
			iterationsWithoutProgress++;
	}
	memcpy(label, shortestLabel, sizeof(shortestLabel));

	cout << endl << shortestDistance<< endl;
	for (size_t i = 0; i < n; i++)
	{
		cout << label[i].x << "  " << label[i].y << endl;
	}
	double sum = 0;
	for (size_t i = 0; i < n; i++)
	{
		sum += path[i].translation;
	}
	cout << sum <<endl;
}