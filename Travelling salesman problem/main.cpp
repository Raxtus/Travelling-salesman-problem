#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

size_t n;

struct POINT
{
	double x, y;
};
POINT *label;


class VECTOR
{
	static size_t pointer;
	double translation;
public:	
	static double distance;
	POINT *begin;
	POINT *end;
	VECTOR()
	{
		begin = &label[pointer];
		pointer = (pointer + 1)%n;
		end = &label[pointer];
	}
	void count()
	{
		double buf = pow(pow(begin->x - end->x, 2) + pow(begin->y - end->y, 2), 1 / 2);
		distance -= buf - translation;
	}
	bool operator <(VECTOR a)
	{
		 if (distance < a.distance) return true;
		 else return false;
	}
	bool operator >(VECTOR a)
	{
		if (distance > a.distance) return true;
		else return false;
	}
};
VECTOR *path;
VECTOR *buff;
	
void permute()
{
	POINT *buffer;
	size_t V1 = rand() % n;
	size_t V2;
	
	buffer = buff[V1].end;
	do V2 = rand() % n;	while (V2 != V1);

	buff[V1].end = buff[V2].end;
	buff[V2].end = buffer;

	buff[V1].count();
	buff[V2].count();
	return;
}

int main(int argc, char* argv[])
{
	const unsigned int maxIteration = 10000000;
	const unsigned int maxIterationWhithoutProgress = 10000;
	srand(time(NULL));

	fstream file;
	file.open("data.txt",ios::in);
	file >> n;
	label = new POINT[n];
	for (int i = 0; i < n; i++)
	{
		file >> label[i].x >> label[i].y;
	}
	file.close();

	buff = new VECTOR[n];
	memcpy(path, buff, sizeof(buff));
		
	unsigned int iterationsWithoutProgress = 0;
	for (int i = 0; i < maxIteration && iterationsWithoutProgress < maxIterationWhithoutProgress; i++)
	{
		permute();
		if (path < buff)
		{
			memcpy(path, buff, sizeof(buff));
			iterationsWithoutProgress = 0;
			std::cout << path->distance;
		}
		else
			iterationsWithoutProgress++;
	}
	delete[] path;
	path = buff;

}