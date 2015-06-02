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

C2EdgeTour *Record;

const int MAXPSIZE = 100;

int Psize = 50;
int Generation = 0;

time_t BeginTime;

inline long long elapsedTime()
{
  return time(0) - BeginTime;
}

inline void startTimer()
{
  BeginTime = time(0);
}

void GA()
{
  /* initialize */
  CLK* lk = new CLK(gNumCity, gNumNN);
  Population.clear();
  Record = new C2EdgeTour(gNumCity);

  /* generate initial random population */
  for (int i=0; i<Psize; i++)
  {
    C2EdgeTour tour(gNumCity);
    tour.makeRandomTour();
    tour.evaluate();
    Population.push_back(tour);
  }

  /* ga loop */
  while (elapsedTime() <= gTimeLimit - 1)
  {
    C2EdgeTour *p1, *p2, *c;

    selection(p1, p2);
    
    crossover(p1, p2, c);
    
    mutation(c, elapsedTime());
    
    lk->run(c);

    c->evaluate();
    
    replacement(p1, p2, c);

    // renew best
    if (Record->getLength() == -1 || c->getLength() < Record->getLength())
      *Record = *c;

    delete c;

    Generation++;

		if (Generation % 100 == 0)
			printf("%lld %lld\n", elapsedTime(), gTimeLimit);
  }

}

void writeAnswer(const char* filename)
{
  FILE* fout = fopen(filename, "w");

  int *orderedPath = new int[gNumCity];
  Record->convertToOrder(orderedPath, gNumCity);

  for (int i=0; i<gNumCity; i++)
    fprintf(fout, "%d ", orderedPath[i] + 1);
  
  fprintf(fout, "\n%lf\n", Record->getLength());
}

void init()
{
  startTimer();
  srand(time(0));
  initParameters(NULL);
}

int main(int argc, char* argv[])
{
  init();

  const char* inputFileName = "cycle.in";
  const char* outputFileName = "cycle.out";

  ReadTspFile(inputFileName); 
  ConstructNN(20);

  GA();

  writeAnswer(outputFileName);

  return 0;
}
