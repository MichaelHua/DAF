#include "rel.h"
#include "global.h"
#include "rel_util.h"

#include <algorithm>

Rel::Rel() {
  cate = EMPTY;
  m = -1;
  isUni = 0;
}

Rel::Rel(B_rel b_rel) {
  cate = b_rel.getCate();
  m = b_rel.getM();
  bRels.push_back(b_rel);
  isUni = 0;
}

Rel::Rel(rel_cate _cate, const int _m) {
  cate = _cate;
  m = _m;
  isUni = 0;
}

Rel::Rel(rel_cate _cate, const int _m, vector<B_rel> _bRels) {
  if (_bRels.size() == 0) {
    Rel();
  } else {
    cate = _cate;
    m = _m;
    bRels = _bRels;
    if (bRels.size() == (unsigned) 4 * m) {
      isUni = 1;
    } else {
      isUni = 0;
    }
  }
}

Rel::Rel(rel_cate _cate, const int _m, vector<int> _segs) {
  if (_segs.size() == 0) {
    Rel();
  } else {
    cate = _cate;
    m = _m;

    if (_segs.size() == (unsigned) 4 * m) {
      isUni = 1;
    } else {
      isUni = 0;
    }

    vector<B_rel> _bRels;

    for (auto i = _segs.begin(); i != _segs.end(); ++i) {
      _bRels.push_back(B_rel(_cate, (*i), _m));
    }

    bRels = _bRels;
  }

}

Rel::Rel(rel_cate _cate, const int _m, bool _isUni) {
  if (_isUni == 0) {
    Rel(_cate, _m);
  } else {

    isUni = 1;
    cate = _cate;
    m = _m;
    for (int seg = 0; seg < 4 * m; seg++) {
      bRels.push_back(B_rel(cate, seg, m));
    }
  }
}

const rel_cate Rel::getCate(void) const {
  return cate;
}

const int Rel::getM(void) const {
  return m;
}

vector<B_rel> Rel::getBRels(void) {
  sortBRels();
  return bRels;
}

void Rel::sortBRels(void) {
  if (!isEmpty()) {
    std::sort(bRels.begin(), bRels.end());
  }
}

const bool Rel::getIsUni(void) const {
  return isUni;
}

bool Rel::isEqual(Rel rel_2) {
  sortBRels();
  rel_2.sortBRels();

  if (getBRels().size() == rel_2.getBRels().size()) {
    vector<B_rel> bRels_1 = getBRels();
    vector<B_rel> bRels_2 = rel_2.getBRels();
    return std::equal(bRels_1.begin(), bRels_1.end(), bRels_2.begin());
  }

  return 0;
}

const bool Rel::isEmpty(void) const {
  if (cate == EMPTY) {
    return true;
  } else {
    return false;
  }
}

string Rel::getStr(void) {
  if (isEmpty()) {
    return "EMPTY";
  }

  if (getBRels().size() == (unsigned) 4 * m) { // universal relation
    return  "{" + config::str_cate[getCate()] + "_U}";
  } else {

    sortBRels();

    int size = (int) bRels.size();
    vector<int> bRelSegs(size);
    for (int i = 0; i < size; i++) {
      bRelSegs.at(i) = bRels.at(i).getSeg();
    }

    vector<int> markers = pretty_print_markers(bRelSegs);
    string str = "{";

    for (int i = 0; i < size; i++) {
      int incr = markers.at(i);
      if (incr == 0) {
        str += bRels.at(i).getStr() + ", ";
      } else {

        str += bRels.at(i).getStr() + " ... " + bRels.at(i + incr).getStr();
        str += ", ";
        i += incr;
      }
    }

    str = str.substr(0, str.length() - 2);
    str += "}";

    return str;
  }
} 
