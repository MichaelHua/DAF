
#ifndef REL_H
#define REL_H

#include <iostream>
#include <vector>
using namespace std;

#include "global.h"
#include "b_rel.h"

class B_rel;

// a relation can be basic or composite
class Rel {
  rel_cate cate; // category of a relation
  int m;
  vector<B_rel> bRels;
  bool isUni;

public:
  Rel();
  Rel(B_rel); // actually a basic relation
  Rel(rel_cate, const int);
  Rel(rel_cate, const int, vector<B_rel>);
  Rel(rel_cate, const int, vector<int>);
  Rel(rel_cate, const int, const bool);

  const rel_cate getCate(void) const;
  const int getM(void) const;
  vector<B_rel> getBRels(void);
  string getStr(void);
  const bool getIsUni(void) const;

  bool isEqual(Rel);
  const bool isEmpty(void) const;

  void sortBRels(void);
};

#endif
