#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lk.h"
#include "cpputil.h"
#include "crossover.h"

#define MAXPSIZE 100

extern long long gTimeLimit;

int Psize = 50;
int Generation = 0;
time_t BeginTime;
C2EdgeTour *Record;

void GA()
{
  CLK* lk;
  C2EdgeTour** population = new C2EdgeTour*[MAXPSIZE];
  Record = new C2EdgeTour(gNumCity);
  lk = new CLK(gNumCity, gNumNN);

  /* generate initial population */
  for (int i=0; i<Psize; i++)
  {
    population[i] = new C2EdgeTour(gNumCity);
    population[i]->makeRandomTour();
    population[i]->evaluate();
  }
  Record = population[0];
  Record->evaluate();

  while(1)
  {
    if (time(NULL) - BeginTime >= gTimeLimit - 1) return;

    C2EdgeTour *c = new C2EdgeTour(gNumCity);
    C2EdgeTour *p1, *p2;

    c->makeRandomTour();

    // selection
    // crossover
    // mutation 1
    lk->run(c);
    // mutation 2
    c->evaluate();
    if (c->getLength() < Record->getLength())
      Record = c;
    // replacement

    Generation++;
    break;
  }
}

void answer(FILE* fp)
{
  int *OrderedPath = new int[gNumCity];
  Record->convertToOrder(OrderedPath, gNumCity);

  for (int i=0; i<gNumCity; i++)
    fprintf(fp, "%d ", OrderedPath[i]+1);
  
  fprintf(fp, "\n%lf\n", Record->getLength());
}

int main(int argc, char* argv[])
{
  BeginTime = time(NULL);

  // TODO : stdin으로 입력받기
  ReadTspFile((char *)"cycle.in"); 
  ConstructNN(20);

  srand(time(0));

  GA();

  FILE *fout = fopen("cycle.out", "w");
  answer(fout);

  return 0;
}