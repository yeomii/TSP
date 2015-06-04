#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <vector>
#include "lk.h"
#include "cpputil.h"
#include "ga.h"

#define affirm(x)    assert(x)

using namespace std;

extern long long gTimeLimit;

vector<C2EdgeTour> Population = vector<C2EdgeTour>();
vector<C2EdgeTour> Population2 = vector<C2EdgeTour>();

C2EdgeTour *Record;

const int MAXPSIZE = 100;

int Psize = 32;
int Generation = 0;
int change = 0;

void LK()
{
	CLK* lk = new CLK(gNumCity, gNumNN);
	Population.clear();
	for (int i=0; i<Psize; i++)
	{
    C2EdgeTour tour(gNumCity);
    tour.makeRandomTour();
		lk->run(&tour);
		tour.evaluate();
    Population.push_back(tour);
	}
	fprintf(stdout, "time : %lf\n", timerRead(0));
	printStats(stdout, Population);
}

void multiStart()
{
	CLK* lk = new CLK(gNumCity, gNumNN);
	Record = new C2EdgeTour(gNumCity);
	C2EdgeTour* tour = new C2EdgeTour(gNumCity);

  double milliTimeLimit = gTimeLimit * 1000;
  while (timerRead(0) <= milliTimeLimit - 500)
  {
		tour->makeRandomTour();
		lk->run(tour);
		tour->evaluate();
    if (Record->getLength() == -1 || tour->getLength() < Record->getLength())
      *Record = *tour;
		if (Generation++ % 100 == 0)
			printf("%d : %lf\n", Generation, Record->getLength());
	}
	printf("%d : %lf\n", Generation, Record->getLength());
}

void GA()
{
  /* initialize */
  CLK* lk = new CLK(gNumCity, gNumNN);
  Population.clear();
  Population2.clear();
  Record = new C2EdgeTour(gNumCity);

  /* generate initial random population */
	for (int p=0; p<1; p++)
	{
		for (int i=0; i<Psize; i++)
		{
			C2EdgeTour tour(gNumCity);
			tour.makeRandomTour();
			tour.evaluate();
			if (p == 0)
				Population.push_back(tour);
			else
				Population2.push_back(tour);
		}
	}
  double milliTimeLimit = gTimeLimit * 1000;
	double originMt = Params.mutation_t;
  /* ga loop */
  while (timerRead(0) <= milliTimeLimit - 500)
  {
    C2EdgeTour *p1, *p2, *c;
		
    //selection(p1, p2, (Generation % 2 == 0) ? Population : Population2);
    selection(p1, p2, Population);

    crossover(p1, p2, c);

    mutation(c, timerRead(0) / milliTimeLimit);

    lk->run(c);

    c->evaluate();

    //replacement(p1, p2, c, (Generation % 2 == 0) ? Population : Population2);
    replacement(p1, p2, c, Population);

    // renew best
    if (Record->getLength() == -1 || c->getLength() < Record->getLength())
      *Record = *c;

    delete c;

    Generation++;

    if (Generation % 100 == 0)
    {
      if (Population[0].getLength() == Population[Population.size() / 4 * 3].getLength())
			{
				for (int i=0; i<Psize; i++)
				{
					Population[i].makeRandomTour();
					Population[i].evaluate();
				}
      }
    }
  }
}

void writeAnswer(const char* filename)
{
  FILE* fout;
	
	if (filename == NULL)
		fout = stdout;
	else
		fout = fopen(filename, "w");

  int *orderedPath = new int[gNumCity];
  Record->convertToOrder(orderedPath, gNumCity);

  for (int i=0; i<gNumCity; i++)
    fprintf(fout, "%d ", orderedPath[i] + 1);

  //fprintf(fout, "\n%lf\n", Record->getLength());
}

void init()
{
  timerInit();
  timerStart(0);
  srand(time(0));
  initParameters(NULL);
}

int main(int argc, char* argv[])
{
  init();

  const char* inputFileName = "cycle.in";
  const char* outputFileName = "cycle.out";

  //ReadTspFile(argc > 1 ? (const char *)argv[1] : inputFileName); 
  ReadTspFile(NULL);
	ConstructNN(20);

  GA();
	//LK();
	//multiStart();
	
	/*
	if (argc > 2)
  	writeAnswer(argv[2]);
	else
	*/
	writeAnswer(NULL);

  return 0;
}
