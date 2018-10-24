#include <math.h>
#include <iostream>
#include <set>
#include <algorithm>

#include "b_rel.h"
#include "rel.h"

using namespace std;

// always normalized to [0, 2pi)
float norm(const float _rad) {
  float rad = _rad;
  while(rad >= 2 * M_PI) rad -= 2 * M_PI;
  while(rad < 0) rad += 2 * M_PI;

  if (abs(rad - 0.0) < config::EPSILON ||
    abs(rad - 2 * M_PI) < config::EPSILON) {

    rad = 0.0;
  }

  return rad;
}

int norm_seg(const int m, const int _seg) {
  int seg = _seg;
  while (seg >= 4 * m) {
    seg -= 4 * m;
  }

  while (seg < 0) {
    seg += 4 * m;
  }

  return seg;
}


int get_MaxSectors(int m) {
  return (4 * m);
}



Rel get_rel_from_bRels(int segStart, int segEnd, rel_cate _cate, int _m) {
  vector<B_rel> bRels;

  segStart = norm_seg(_m, segStart);
  segEnd = norm_seg(_m, segEnd);

  if (segStart <= segEnd) {
    for (int seg = segStart; seg <= segEnd; seg++) {
      bRels.push_back(B_rel(_cate, seg, _m));
    }
  } else {
    for (int seg = segStart; seg < 4 * _m; seg++) {
      bRels.push_back(B_rel(_cate, seg, _m));
    }

    for (int seg = 0; seg <= segEnd; seg++) {
      bRels.push_back(B_rel(_cate, seg, _m));
    }
  }

  return Rel(_cate, _m, bRels);
}

bool isOdd(int i) {
  return i % 2 == 1;
}

bool isEven(int i) {
  return i % 2 == 0;
}

int delta(int i) {
  if (isEven(i)) {
    return 1;
  } else {
    return 0;
  }
}

Rel omega(int i, int j, int k, rel_cate cate, int m) {
  if (isEven(i) || isEven(j)) { // i or j are even.
    return Rel(B_rel(cate, norm_seg(m, k), m));
  } else { // if i and j are odd

    vector<B_rel> bRels;
    bRels.push_back(B_rel(cate, norm_seg(m, k - 1), m));
    bRels.push_back(B_rel(cate, norm_seg(m, k), m));
    bRels.push_back(B_rel(cate, norm_seg(m, k + 1), m));

    return Rel(cate, m, bRels);
  }
}

int psi(int i, int j) {
  if (isEven(i) && isEven(j)) { // i and j are even.
    return 1;
  }

  if (isOdd(i) && isOdd(j)) { // i and j are odd.
    return -1;
  }

  return 0;
}

vector<int> getSegs(Rel r) {
  vector<int> segs;
  vector<B_rel> bRels = r.getBRels();

  for (auto seg = bRels.begin(); seg != bRels.end(); ++seg) {
    segs.push_back((*seg).getSeg());
  }

  return segs;
}

Rel cup(Rel r1, Rel r2) {
  // don't check their types here because one of them might be EMPTY.
  if (r1.isEmpty()) {
    return Rel(r2);
  }

  if (r2.isEmpty()) {
    return Rel(r1);
  }

  if (r1.getCate() != r2.getCate() || r1.getM() != r2.getM()) {
    return Rel();
  }

  r1.sortBRels();
  r2.sortBRels();

  vector<int> r1_segs = getSegs(r1);
  vector<int> r2_segs = getSegs(r2);
  r1_segs.insert(r1_segs.end(), r2_segs.begin(), r2_segs.end());

  // remove duplicates
  set<int> s(r1_segs.begin(), r1_segs.end());
  r1_segs.assign(s.begin(), s.end());

  return Rel(r1.getCate(), r1.getM(), r1_segs);
}



Rel cap(Rel r1, Rel r2) {
  if (r1.isEmpty() || r2.isEmpty()) {
    return Rel();
  }

  if (r1.getCate() != r2.getCate() || r1.getM() != r2.getM()) {
    return Rel();
  }

  vector<int> r1_segs = getSegs(r1);
  vector<int> r2_segs = getSegs(r2);
  vector<int> r3_segs;
  sort(r1_segs.begin(), r1_segs.end());
  sort(r2_segs.begin(), r2_segs.end());

  set_intersection(r1_segs.begin(), r1_segs.end(),
    r2_segs.begin(), r2_segs.end(), back_inserter(r3_segs));

  return Rel(r1.getCate(), r1.getM(), r3_segs);
}

vector<int> pretty_print_markers(vector<int> bRelSegs) {
  int size = (int) bRelSegs.size();
  vector<int> markers(size);

  int flag = 0;
  int pre = -100;
  int incr = 0;
  int counter = 0;

  for (auto it = bRelSegs.begin(); it != bRelSegs.end(); it++) {
    flag = (*it);

    if (flag == pre + 1) {
      incr++;
    } else {

      if (incr > 2) {
        markers[counter - incr - 1] = incr;
      }

      incr = 0;
    }

    pre = flag;
    counter++;
  }

  //
  if (incr > 2) {
    markers[counter - incr - 1] = incr;
  }

  return markers;
}
