#ifndef __GA_H__
#define __GA_H__

#include <vector>
#include "lk.h"

/* Enums */

enum SelectionType
{
  Random = 0,
  Tournament = 1
};

enum CrossoverType
{
  PMX = 0,
  EdgeRecombination = 1
};

enum ReplacementType
{
  Worst = 0,
  Preselection = 1,
  GBA = 2
};

const char* getString(SelectionType);
const char* getString(CrossoverType);
const char* getString(ReplacementType);

/* Params */

typedef struct {
  SelectionType selectionType;
  CrossoverType crossoverType;
  ReplacementType replacementType;

  int tournament_k;
  double tournament_t;

  double mutation_t; // threshold
  double mutation_b; // if larger than 1, non-uniform

  double generationGap; // if 0, steady-state GA and 1, generational GA 

  int printFreq;
} Parameter;

extern Parameter Params;

void initParameters(const char* fname);
void printParameters(FILE* fout);
void printStats(FILE* file);

void timerInit();
void timerClear(int i);
void timerStart(int i);
void timerStop(int i);
double timerRead(int i);
unsigned timerCount(int i);

/* GA Operators */

extern vector<C2EdgeTour> Population;

void selection(C2EdgeTour*& p1, C2EdgeTour*& p2);
void crossover(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour*& c);
void mutation(C2EdgeTour* c, double timePortion);
void replacement(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour* c);

#endif
