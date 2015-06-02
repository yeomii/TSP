#include "ga.h"

const char* getString(SelectionType selectionType)
{
  static const char* dic[] = {
    "Random",
    "Tournament"
  };

  return dic[(unsigned char)selectionType];
}

const char* getString(CrossoverType crossoverType)
{
  static const char* dic[] = {
    "PMX",
    "EdgeRecombination"
  };

  return dic[(unsigned char)crossoverType];
}

const char* getString(ReplacementType replacementType)
{
  static const char* dic[] = {
    "Worst",
    "Preselection",
    "GBA"
  };

  return dic[(unsigned char)replacementType];
}
