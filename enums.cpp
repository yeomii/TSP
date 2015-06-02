#include "ga.h"

string getString(SelectionType selectionType)
{
  static string dic[] = {
    "Random",
    "Tournament"
  };

  return dic[(unsigned char)selectionType];
}

string getString(CrossoverType crossoverType)
{
  static string dic[] = {
    "PMX",
    "EdgeRecombination"
  };

  return dic[(unsigned char)crossoverType];
}

string getString(ReplacementType replacementType)
{
  static string dic[] = {
    "Worst",
    "Preselection",
    "GBA"
  };

  return dic[(unsigned char)replacementType];
}