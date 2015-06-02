#include "ga.h"

Parameter Params;

void initParameters(const char *fname)
{
  if (fname == NULL)
  {
    Params.selectionType = Tournament;
    Params.tournament_k = 5;
    Params.tournament_t = 0.7;
    Params.crossoverType = PMX;
    Params.mutation_t = 0.05;
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