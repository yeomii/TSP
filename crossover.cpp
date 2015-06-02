#include <algorithm>
#include "ga.h"

int _p1[1500];
int _p2[1500];
int _c[1500];
int _pos[1500];

void pmx(int* p1, int* p2, int* c, int size)
{
	int left = rand() % size;
	int right = (left + (rand() % (size - 1))) % size;

	fill(c, c + size, 0);
	fill(_pos, _pos + size, -1);

	for (int i = left; i != right; i = (i + 1) % size)
	{
		c[i] = p1[i];
		_pos[p1[i]] = i;
	}

	for (int i = right; i != left; i = (i + 1) % size)
	{
		int val = p2[i];
		while (_pos[val] != -1)
		{
			int nextPos = _pos[val];
			val = p2[nextPos];
		}
		c[i] = val;
	}
}

C2EdgeTour pmx(C2EdgeTour& p1, C2EdgeTour& p2)
{
	int size = p1.getSize();
	p1.convertToOrder(_p1, size);
	p2.convertToOrder(_p2, size);

	pmx(_p1, _p2, _c, size);

	C2EdgeTour ret(size);
	ret.convertFromOrder(_c, size);
	return ret;
}