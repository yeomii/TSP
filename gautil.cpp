#include <algorithm>
#include <chrono>
#include <math.h>
#include "ga.h"

#define NUM_TIMERS    64

using namespace std;
using namespace chrono;

static system_clock::time_point t_start[NUM_TIMERS];
static double t_elapsed[NUM_TIMERS];
static unsigned t_count[NUM_TIMERS];

extern int Generation;
extern vector<C2EdgeTour> Population;
Parameter Params;

void initParameters(const char *fname)
{
  if (fname == NULL)
  {
    Params.selectionType = Tournament;
    Params.tournament_k = 5;
    Params.tournament_t = 0.7;
    Params.crossoverType = PMX;
    Params.mutation_t = 0.15;
    Params.mutation_b = 1;
    Params.replacementType = GBA;
    Params.generationGap = 0;
    Params.printFreq = 100;
  }
  else
  {
    FILE *fin = fopen(fname, "r");
    fscanf(fin, "s:%d tk:%d tt:%lf c:%d mt:%lf mb:%lf r:%d gg:%lf pf:%d",
      &Params.selectionType,
      &Params.tournament_k,
      &Params.tournament_t,
      &Params.crossoverType,
      &Params.mutation_t,
      &Params.mutation_b,
      &Params.replacementType,
      &Params.generationGap,
      &Params.printFreq);
		fclose(fin);
  }
}

void printParameters(FILE *fout)
{
  fprintf(fout, "Selection: %s\n", getString(Params.selectionType));
  fprintf(fout, "Tournament_k: %lf\n", Params.tournament_k);
  fprintf(fout, "Tournament_t: %lf\n", Params.tournament_t);
  fprintf(fout, "Crossover: %s\n", getString(Params.crossoverType));
  fprintf(fout, "Mutation_t: %lf\n", Params.mutation_t);
  fprintf(fout, "Mutation_b: %lf\n", Params.mutation_b);
  fprintf(fout, "Replacement: %s\n", getString(Params.replacementType));
  fprintf(fout, "generationGap: %lf\n", Params.generationGap);
  fprintf(fout, "printFrequency: %d\n", Params.printFreq);
}

void printStats(FILE *file, vector<C2EdgeTour>& population){
  if (Generation % Params.printFreq != 0)
    return;
  int Psize = population.size();

  sort(population.begin(), population.end());

  double sum = 0.0;
  for (int i = 0; i < Psize; i++) {
    sum += population[i].getLength();
  }
  double mean = sum / Psize;

  double sq_sum = 0.0;
  for (int i = 0; i < Psize; i++) {
    sq_sum += population[i].getLength() * population[i].getLength();
  }
  double stdev = sqrt(sq_sum / Psize - mean * mean);

  fprintf(file, "gen:%d avg:%.2f stdev:%.2f q0:%.2f q1:%.2f q2:%.2f q3:%.2f q4:%.2f\n",
    Generation, mean, stdev,
    population[0].getLength(), population[Psize / 4].getLength(), 
    population[Psize / 2].getLength(), population[3 * Psize / 4].getLength(), 
    population[Psize - 1].getLength());
}

static inline system_clock::time_point getTime()
{
  return system_clock::now();
}


void timerInit() 
{
  int i;
  for (i = 0; i < NUM_TIMERS; i++) {
    t_elapsed[i] = 0.0;
    t_count[i] = 0;
  }
}


void timerClear(int i) 
{
  t_elapsed[i] = 0.0;
  t_count[i] = 0;
}


void timerStart(int i) 
{
  t_start[i] = getTime();
}


void timerStop(int i) 
{
  t_elapsed[i] += duration_cast<milliseconds>(getTime() - t_start[i]).count();
  t_count[i]++;
}


double timerRead(int i) 
{
  t_elapsed[i] += duration_cast<milliseconds>(getTime() - t_start[i]).count();
  t_start[i] = getTime();
  return t_elapsed[i];
}


unsigned timerCount(int i) 
{
  return t_count[i];
}
