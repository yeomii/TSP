#include <algorithm>
#include <assert.h>
#include <math.h>
#include "tsplib_io.h"
#include "ga.h"

extern long long gTimeLimit;
extern vector<C2EdgeTour> Population;
extern Parameter Params;

#pragma region SELECTION

void randomSelection(C2EdgeTour*& p1, C2EdgeTour*& p2)
{
  int first = rand() % Population.size();
  int gap = rand() % (Population.size() - 2) + 1;
  int second = (first + gap) % Population.size();

  p1 = &Population[first];
  p2 = &Population[second];
}

void tournamentSelection(C2EdgeTour*& p1, C2EdgeTour*& p2)
{
  int candidates = 1 << Params.tournament_k;
  int *selected = new int[Population.size()];

  for (int i = 0; i < Population.size(); i++)
    selected[i] = i;
  for (int i = 0; i < candidates; i++)
    swap(selected[i], selected[i + rand() % (Population.size() - i)]);

  for (int step = 0; step < Params.tournament_k - 1; step++)
  {
    candidates /= 2;
    for (int i = 0; i < candidates; i++)
    {
      double f1 = Population[selected[2 * i]].getLength();
      double f2 = Population[selected[2 * i + 1]].getLength();
      double r = ((double)rand() / (RAND_MAX));
      if (r < Params.tournament_t)
        selected[i] = (f1 < f2) ? selected[2 * i] : selected[2 * i + 1];
      else
        selected[i] = (f1 < f2) ? selected[2 * i + 1] : selected[2 * i];
    }

  }
  p1 = &Population[selected[0]];
  p2 = &Population[selected[1]];

  delete[] selected;

  assert(p1 != p2);
}

void selection(C2EdgeTour*& p1, C2EdgeTour*& p2)
{
  switch (Params.selectionType)
  {
  case Tournament:
    tournamentSelection(p1, p2);
    break;
  default:
    randomSelection(p1, p2);
    break;
  }
}

#pragma endregion

#pragma region CROSSOVER

int _p1[1500];
int _p2[1500];
int _c[1500];
int _pos[1500];

void pmx(int* p1, int* p2, int* c, int size)
{
  int left = rand() % size;
  int gap = rand() % (size - 2) + 1;
  int right = (left + gap) % size;

  fill(c, c + size, 0);
  fill(_pos, _pos + size, -1);

  for (int i = left; i != right; i = (i + 1) % size)
  {
    c[i] = p1[i];
    _pos[p1[i]] = i;
  }

  for (int i = right; i != left; i = (i + 1) % size)
  {
    int val = p2[i];
    while (_pos[val] != -1)
    {
      int nextPos = _pos[val];
      val = p2[nextPos];
    }
    c[i] = val;
  }
  if (c[0] == c[1])
    c[0] = -1;
}

void pmx(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour*& c)
{
  int size = p1->getSize();
  p1->convertToOrder(_p1, size);
  p2->convertToOrder(_p2, size);

  pmx(_p1, _p2, _c, size);

  c = new C2EdgeTour(size);
  c->convertFromOrder(_c, size);
}

void edgeRecombination(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour*& c)
{
  // TODO
}

void crossover(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour*& c)
{
  switch (Params.crossoverType)
  {
  case PMX:
    pmx(p1, p2, c);
    break;
  case EdgeRecombination:
    edgeRecombination(p1, p2, c);
    break;
  }
}

#pragma endregion

#pragma region MUTATION

void changeTwo(int* order, int begin)
{
  int end = rand() % gNumCity + 1;
  if (end < begin)
    swap(begin, end);
  reverse(order + begin, order + end);
}

void changeOr(int* order, int begin)
{
  int end = rand() % gNumCity + 1;
  if (end < begin)
    swap(begin, end);
  else if (end == begin)
    return;
  reverse(order + begin, order + end);
  reverse(order + begin, order + end - 1);
}

void changeSwap(int *order, int idx)
{
  int target = rand() % gNumCity;
  swap(order[idx], order[target]);
}

void uniformMutation(C2EdgeTour* c, double threshold)
{
  c->convertToOrder(_c, gNumCity);
  for (int i = 0; i < Population.size(); i++){
    double r = (double)rand() / RAND_MAX;
    if (r < threshold){
      int sel = rand() % 3;
      switch (sel){
      case 0:
        changeTwo(_c, i);
        break;
      case 1:
        changeOr(_c, i);
        break;
      case 2:
        changeSwap(_c, i);
        break;
      }
    }
  }
  c->convertFromOrder(_c, gNumCity);
}


void mutation(C2EdgeTour* c, long long elapsedTime)
{
  double th = Params.mutation_t;
  if (Params.mutation_b > 1)
  {
    double timePortion = ((double)elapsedTime / (double)gTimeLimit);
    th = 1 - pow(th, pow(1 - timePortion, Params.mutation_b));
    th *= Params.mutation_t;
  }

  uniformMutation(c, th);
}

#pragma endregion

#pragma region REPLACEMENT

void worstReplacement(C2EdgeTour* c)
{
  vector<C2EdgeTour>::iterator worstElem = 
    max_element(Population.begin(), Population.end());
  
  *worstElem = *c;
}

void preselection(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour* c)
{
  if (p1->getLength() > p2->getLength())
    *p1 = *c;
  else
    *p2 = *c;
}

void gba(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour* c)
{
  if (p1->getLength() < c->getLength() && p2->getLength() < c->getLength())
    worstReplacement(c);
  else
    preselection(p1, p2, c);
}

/* Replacement에서는 다음 내용을 구현해야 한다.
     - p1과 p2의 정보를 이용해서 Population중 하나를 c에서
       복사한 내용으로 바꾸어야 한다.
     - Population에서 제외된 투어는 반드시 삭제해 주어야 한다.
   Replacement를 호출할 때는 다음과 같은 상태를 가정한다.
     - p1, p2, c는 이미 evaluate 된 상태여야 한다.
 */
void replacement(C2EdgeTour* p1, C2EdgeTour* p2, C2EdgeTour* c)
{
  switch (Params.replacementType)
  {
  case Worst:
    worstReplacement(c);
    break;
  case Preselection:
    preselection(p1, p2, c);
    break;
  case GBA:
    gba(p1, p2, c);
    break;
  }
}

#pragma endregion
