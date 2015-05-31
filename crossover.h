#ifndef __CROSSOVER_H__
#define __CROSSOVER_H__

#include <string>
#include "lk.h"
using namespace std;

namespace Crossover
{
	enum Crossover
	{
		PMX,
		EdgeRecombination
	};

	string getString(Crossover);

	void PMX(int* p1, int* p2, int* c, int size);
	C2EdgeTour PMX(C2EdgeTour& p1, C2EdgeTour& p2);
	C2EdgeTour EdgeRecombination(C2EdgeTour& p1, C2EdgeTour& p2);
}

#endif