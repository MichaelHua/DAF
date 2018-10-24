
#ifndef DAF_H
#define DAF_H

#include <iostream>
#include <vector>
#include "b_rel.h"
using namespace std;



class Daf {

  int m; // granularity
  vector<B_rel> bRels; // basic relations

  void initBRels(void);

public:
  Daf(const int);

  const int getM(void) const;
  const vector<B_rel> getBRels(void) const;

  string getBRelsStr(void);
};

#endif
