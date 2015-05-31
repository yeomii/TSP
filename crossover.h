#ifndef __CROSSOVER_H__
#define __CROSSOVER_H__

#include <string>
#include "lk.h"
using namespace std;

namespace crossover
{
	enum Crossover
	{
		PMX,
		EdgeRecombination
	};

	string getString(Crossover);

	C2EdgeTour PMX(C2EdgeTour& p1, C2EdgeTour& p2);
	C2EdgeTour EdgeRecombination(C2EdgeTour& p1, C2EdgeTour& p2);
}

#endif