
#ifndef REL_UTIL_H
#define REL_UTIL_H

#include "b_rel.h"
#include "rel.h"

float norm(const float);
int norm_seg(const int, const int);

int get_MaxSectors(int);


Rel get_rel_from_bRels(int, int, rel_cate, int);

int delta (int);

bool isOdd (int);
bool isEven (int);

Rel omega(int, int, int, rel_cate, int);
int psi(int, int);

Rel cup(Rel, Rel); // union of two relations
Rel cap(Rel, Rel); // intersection of two relations

vector<int> getSegs(Rel);

vector<int> pretty_print_markers(vector<int>);



#endif
