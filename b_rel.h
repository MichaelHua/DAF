
#ifndef B_REL_H
#define B_REL_H

#include <iostream>
using namespace std;

#include "global.h"

class Rel;

class B_rel {
  rel_cate cate; // category of a relation
  int seg;
  int m; // granularity

public:
  B_rel();
  B_rel(rel_cate, const int);
  B_rel(rel_cate, const int, const int);

  const rel_cate getCate(void) const;
  const int getSeg(void) const;
  const int getM(void) const;
  const string getStr(void) const;

  const bool isEqual(const B_rel) const;
  const bool isEmpty(void) const;

  const bool operator<(const B_rel);
  const bool operator==(const B_rel);
};

#endif
