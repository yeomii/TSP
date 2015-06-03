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
int change = 0;

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

  gTimeLimit = 20;
  double milliTimeLimit = gTimeLimit * 1000;
  /* ga loop */
  while (timerRead(0) <= milliTimeLimit - 500)
  {
    C2EdgeTour *p1, *p2, *c;

    timerStart(1);
    selection(p1, p2);
    timerStop(1);

    timerStart(2);
    crossover(p1, p2, c);
    timerStop(2);

    timerStart(3);
    mutation(c, timerRead(0) / milliTimeLimit);
    timerStop(3);

    timerStart(4);
    lk->run(c);
    timerStop(4);

    timerStart(5);
    c->evaluate();
    timerStop(5);

    timerStart(6);
    replacement(p1, p2, c);
    timerStop(6);

    // renew best
    if (Record->getLength() == -1 || c->getLength() < Record->getLength())
      *Record = *c;

    delete c;

    Generation++;

    if (Generation % 100 == 0)
    {
      printf("%.0lf ", timerRead(0));
      printStats(stdout);
      double bestLength = Population[0].getLength();
      if (Population[0].getLength() == Population[Population.size() / 4 * 3].getLength())
      {
        printf("population changing...\n", change);
        change++;
        for (int i = 0; i < Psize; i++)
        {
          if (Population[i].getLength() != bestLength)
            break;
          Population[i].makeRandomTour();
          Population[i].evaluate();
        }
      }
      if (bestLength == Population[Population.size() / 2].getLength())
      {
        Params.selectionType = Random;
        Params.mutation_t = 0.15;
      }
      else if (bestLength == Population[Population.size() * 3 / 4].getLength())
      {
        Params.selectionType = Random;
        Params.mutation_t = 0.3;
      }
      else
      {
        Params.selectionType = Tournament;
        Params.mutation_t = 0.05;
      }
    }
  }
  printf("%d ", change);
  printf("%lf %lf %lf %lf %lf %lf", timerRead(1), timerRead(2), timerRead(3), 
    timerRead(4), timerRead(5), timerRead(6));
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

  ReadTspFile(inputFileName); 
  ConstructNN(20);

  GA();

  writeAnswer(outputFileName);

  return 0;
}
