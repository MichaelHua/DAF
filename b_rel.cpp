#include <iostream>
using namespace std;

#include "b_rel.h"
#include "global.h"
#include "rel.h"
#include "rel_util.h"


B_rel::B_rel() {
  cate = EMPTY; // empty
  seg = -1; // unknown
  m = -1; // unknown
}

B_rel::B_rel(rel_cate _cate, const int _seg) {
  cate = _cate;
  seg = _seg;
  m = -1;
}

B_rel::B_rel(rel_cate _cate, const int _seg, int _m) {
  cate = _cate;
  seg = _seg;
  m = _m;
}

const string B_rel::getStr(void) const {
  if (isEmpty()) {
    return config::str_cate[EMPTY];
  }

  return config::str_cate[cate] + "_" + to_string(seg);
}

const int B_rel::getSeg(void) const {
  return seg;
}

const int B_rel::getM(void) const {
  return m;
}

const rel_cate B_rel::getCate(void) const {
  return cate;
}


const bool B_rel::isEqual(const B_rel r2) const {
  if (cate == r2.getCate() && seg == r2.getSeg()) {
    return true;
  }

  return false;
}


const bool B_rel::isEmpty(void) const {
  if (cate == EMPTY) {
    return true;
  } else {
    return false;
  }
}

const bool B_rel::operator<(const B_rel r2) {
  return norm_seg(getM(), getSeg()) < norm_seg(getM(), r2.getSeg());
}

const bool B_rel::operator==(const B_rel r2) {
  if (getM() == r2.getM()) {
    if (getCate() == r2.getCate()) {
      if (norm_seg(getM(), getSeg()) == norm_seg(getM(), r2.getSeg())) {
        return 1;
      }
    }
  }

  return 0;
}
