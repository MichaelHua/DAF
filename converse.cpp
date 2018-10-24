#include <iostream>
using namespace std;

#include "global.h"
#include "b_rel.h"
#include "rel.h"
#include "converse.h"
#include "rel_util.h"


// get the converse of ternary same position relations
B_rel get_t_con_sampos(int a1, int a2, int a3, t_con _t_con) {
  int a[] = {a1, a2, a3};
  int b = _t_con;
  int b1 = b / 100;
  int b2 = (b - 100 * b1) / 10;
  int b3 = b - 100 * b1 - 10 * b2;

  int c[] = {-1, -1, -1};
  c[0] = a[b1 - 1];
  c[1] = a[b2 - 1];
  c[2] = a[b3 - 1];

  if (c[0] == c[1]) {
    return B_rel(SAMPOS, 12);
  }

  if (c[1] == c[2]) {
    return B_rel(SAMPOS, 23);
  }

  if (c[0] == c[2]) {
    return B_rel(SAMPOS, 13);
  }

  return B_rel();
}

Rel get_t_con_inv(B_rel bRel) {
  int m = bRel.getM();
  int i = norm_seg(m, bRel.getSeg());

  if (i == 0) {
    return Rel(B_rel(RELA, 2 * m, m));
  }

  if (i == 2 * m) {
    vector<B_rel> bRels;
    bRels.push_back(B_rel(RELA, 0, m));
    bRels.push_back(B_rel(RELA, 2 * m, m));
    return Rel(RELA, m, bRels);
  }

  if (i > 0 && i < 2 * m) {
    return get_rel_from_bRels(2 * m + 1, i + 2 * m - delta(i), RELA, m);
  }

  if (i > 2 * m && i < 4 * m) {
    return get_rel_from_bRels(i - 2 * m + delta(i), 2 * m - 1, RELA, m);
  }

  return Rel(B_rel());
}

Rel get_t_con_sci(B_rel bRel) {
  int m = bRel.getM();
  int i = norm_seg(m, bRel.getSeg());

  if (i == 0) {
    return Rel(B_rel(RELA, 2 * m, m));
  }

  if (i == 2 * m) {
    vector<B_rel> bRels;
    bRels.push_back(B_rel(RELA, 0, m));
    bRels.push_back(B_rel(RELA, 2 * m, m));
    return Rel(RELA, m, bRels);
  }

  if (i > 0 && i < 2 * m) {
    int segStart = norm_seg(m, -1 * (i + 2 * m - delta(i)));
    int segEnd = norm_seg(m, -1 * (2 * m + 1));
    return get_rel_from_bRels(segStart, segEnd, RELA, m);
  }

  if (i > 2 * m && i < 4 * m) {
    int segStart = norm_seg(m, -1 * (2 * m - 1));
    int segEnd = norm_seg(m, -1 * (i - 2 * m + delta(i)));
    return get_rel_from_bRels(segStart, segEnd, RELA, m);
  }

  return Rel(B_rel());
}

Rel get_t_con_hmi(B_rel bRel) {
  int m = bRel.getM();
  return Rel(B_rel(bRel.getCate(), norm_seg(m, -1 * bRel.getSeg()), m));
}

Rel converse(B_rel bRel) {
  int m = bRel.getM();
  int seg = bRel.getSeg();
  rel_cate cate = bRel.getCate();

  if (bRel.isEmpty()) {
    return Rel(B_rel());
  }

  if (cate == SAMPOS) {
    if (seg == 2) {
      return Rel(B_rel(SAMPOS, 2));
    }
  }

  if (m > 0) {
    if (cate  == ABSO) {
      return Rel(B_rel(ABSO, norm_seg(m, seg + 2 * m), m));
    }

    if (cate  == PHI) {
      return Rel(B_rel(PHI, norm_seg(m, -1 * seg), m));
    }
  }

  return Rel(B_rel()); // return an empty relation
}

Rel converse(B_rel bRel, t_con _t_con) {
  int m = bRel.getM();

  if (bRel.isEmpty()) {
    return Rel(B_rel());
  }

  if (bRel.getCate() == SAMPOS) {
    if (bRel.getSeg() == 3) {
      return Rel(B_rel(SAMPOS, 3));
    }

    if (bRel.getSeg() == 12) {
      return Rel(get_t_con_sampos(1, 1, 0, _t_con));
    }

    if (bRel.getSeg() == 23) {
      return Rel(get_t_con_sampos(0, 1, 1, _t_con));
    }

    if (bRel.getSeg() == 13) {
      return Rel(get_t_con_sampos(1, 0, 1, _t_con));
    }
  }


  if (m > 0) {
    if (bRel.getCate() == RELA) {
      if (_t_con == INV || _t_con == SC) {
        return get_t_con_inv(bRel);
      }

      if (_t_con == SCI || _t_con == HM) {
        return get_t_con_sci(bRel);
      }

      if (_t_con == HMI) {
        return get_t_con_hmi(bRel);
      }
    }
  }

  return Rel(B_rel()); // return an empty relation
}

Rel converse(B_rel bRel, B_rel phi_rel) {
  int m = bRel.getM();

  if (bRel.isEmpty() || m <= 0 || phi_rel.getCate() != PHI
    || m != phi_rel.getM()) {

    return Rel(B_rel());
  }

  if (bRel.getCate() == INTR) {
    int i = bRel.getSeg();
    int j = phi_rel.getSeg();
    int z = i + 2 * m - j;

    return omega(i, j, z, INTR, m);
  }

  return Rel(B_rel());
}

Rel converse(Rel rel) {
  vector<B_rel> bRels = rel.getBRels();
  Rel result;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    result = cup(result, converse(*it));
  }

  return result;
}

Rel converse(Rel rel, t_con _t_con) {
  vector<B_rel> bRels = rel.getBRels();
  Rel result;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    result = cup(result, converse(*it, _t_con));
  }

  return result;
}

Rel converse(Rel rel, Rel phi_rel) {
  vector<B_rel> bRels = rel.getBRels();
  vector<B_rel> phi_bRels = phi_rel.getBRels();
  Rel result;

  for (auto it_1 = bRels.begin(); it_1 != bRels.end(); it_1++) {
    for (auto it_2 = phi_bRels.begin(); it_2 != phi_bRels.end(); it_2++) {
      result = cup(result, converse(*it_1, *it_2));
    }
  }

  return result;
}
