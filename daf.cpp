
#include "daf.h"
#include <iostream>

using namespace std;

Daf::Daf(const int _m) {
  m = _m;
  initBRels();

  // cout << "Daf_" << m << "!" << endl;
}

void Daf::initBRels(void) {
  bRels.push_back(B_rel(SAMPOS, 2));
  bRels.push_back(B_rel(SAMPOS, 12));
  bRels.push_back(B_rel(SAMPOS, 23));
  bRels.push_back(B_rel(SAMPOS, 13));
  bRels.push_back(B_rel(SAMPOS, 3));

  for (int i = 0; i < 4 * m; i++) {
    bRels.push_back(B_rel(ABSO, i, m));
  }

  for (int i = 0; i < 4 * m; i++) {
    bRels.push_back(B_rel(INTR, i, m));
  }

  for (int i = 0; i < 4 * m; i++) {
    bRels.push_back(B_rel(RELA, i, m));
  }

  for (int i = 0; i < 4 * m; i++) {
    bRels.push_back(B_rel(PHI, i, m));
  }
}

string Daf::getBRelsStr(void) {

  string str = "{S_2, S_12, S_23, S_13, S3";

  int m = getM();
  if (m > 0) {
    string last = to_string(4 * m - 1);
    str += ", A_0 ... A_" + last + ", ";
    str += "I_0 ... I_" + last + ", ";
    str += "R_0 ... R_" + last + ", ";
    str += "P_0 ... P_" + last;
  }
  str += "}";

  return str;
}

const vector<B_rel> Daf::getBRels(void) const {
  return bRels;
}

const int Daf::getM(void) const {
  return m;
}
