#include <iostream>
using namespace std;

#include "global.h"
#include "b_rel.h"
#include "rel.h"
#include "rel_util.h"
#include "b_com.h"

Rel b_com_phi(B_rel r1, B_rel r2) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, i + j);

  return omega(i, j, gap, PHI, m);
}

Rel b_com_phi_infer(B_rel r1, B_rel r2) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, i - j);

  return omega(i, j, gap, PHI, m);
}

Rel b_com_aar(B_rel r1, B_rel r2) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, j - i);

  return omega(i, j, gap, RELA, m);
}

Rel b_com_ara(B_rel r1, B_rel r2) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, i + j);

  return omega(i, j, gap, ABSO, m);
}

Rel b_com_raa(B_rel r1, B_rel r2) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, j - i);

  return omega(i, j, gap, ABSO, m);
}

Rel b_com_iri(B_rel r1, B_rel r2) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, i + j + 2 * m);

  return omega(i, j, gap, INTR, m);
}

Rel b_com_rii(B_rel r1, B_rel r2) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, j - i + 2 * m);

  return omega(i, j, gap, INTR, m);
}

Rel b_com_aaa(B_rel r1, B_rel r2) {

  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap = norm_seg(m, j - i);


  if (gap == 0) {
    return Rel(B_rel(ABSO, i, m));
  }

  if (gap == 2 * m && isOdd(i)) {
    return Rel(ABSO, m, true); // a universal relation
  }

  if (gap == 2 * m && isEven(i)) {
    vector<B_rel> bRels;
    bRels.push_back(B_rel(ABSO, i, m));
    bRels.push_back(B_rel(ABSO, j, m));

    return Rel(ABSO, m, bRels);
  }

  if (gap > 0 && gap < 2 * m) {
    int segStart = norm_seg(m, i + delta(i));
    int segEnd = norm_seg(m, j - delta(j));
    return get_rel_from_bRels(segStart, segEnd, ABSO, m);
  }

  if (gap > 2 * m && gap < 4 * m) {
    int segStart = norm_seg(m, j + delta(j));
    int segEnd = norm_seg(m, i - delta(i));
    return get_rel_from_bRels(segStart, segEnd, ABSO, m);
  }

  return Rel();
}

Rel b_com_tau(B_rel r1, B_rel r2, com_sub_type sub_type) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());
  int gap;


  if (sub_type == II) { // Rule 3
    gap = norm_seg(m, i - j + 2 * m);
    return omega(i, j, gap, INTR, m);
  } else {

    gap = norm_seg(m, i - j);

    if (sub_type == AI || sub_type == RI) { // Rule 1 and 7
      return omega(i, j, gap, INTR, m);
    }

    if (sub_type == IA || sub_type == RA) { // Rule 2 and 5
      return omega(i, j, gap, ABSO, m);
    }

    if (sub_type == AR || sub_type == IR) { // Rule 4 and 6
      return omega(i, j, gap, RELA, m);
    }
  }

  return Rel();
}

Rel b_com_rrr(B_rel r1, B_rel r2, com_sub_type sub_type) {
  int m = r1.getM();
  int i = norm_seg(m, r1.getSeg());
  int j = norm_seg(m, r2.getSeg());

  if (sub_type == R_31) {
    if (j == 0) {
      return Rel(B_rel(RELA, i, m));
    }

    if (j == 2 * m) {
      vector<B_rel> bRels;
      bRels.push_back(B_rel(RELA, i, m));
      bRels.push_back(B_rel(RELA, norm_seg(m, i + 2 * m), m));

      return Rel(RELA, m, bRels);
    }

    if (j > 0 && j < 2 * m) {
      int segStart = norm_seg(m, i + delta(i));
      int segEnd = norm_seg(m, i + j - psi(i, j));
      return get_rel_from_bRels(segStart, segEnd, RELA, m);
    }

    if (j > 2 * m && j < 4 * m) {
      int segStart = norm_seg(m, i + j + psi(i, j));
      int segEnd = norm_seg(m, i - delta(i));
      return get_rel_from_bRels(segStart, segEnd, RELA, m);
    }
  }

  if (sub_type == R_32) {
    if (i == 0) {
      return Rel(B_rel(RELA, j, m));
    }

    if (i == 2 * m) {
      vector<B_rel> bRels;
      bRels.push_back(B_rel(RELA, j, m));
      bRels.push_back(B_rel(RELA, norm_seg(m, j + 2 * m), m));

      return Rel(RELA, m, bRels);
    }

    if (i > 0 && i < 2 * m) {
      int segStart = norm_seg(m, j + delta(j));
      int segEnd = norm_seg(m, i + j - psi(i, j));
      return get_rel_from_bRels(segStart, segEnd, RELA, m);
    }

    if (i > 2 * m && i < 4 * m) {
      int segStart = norm_seg(m, i + j + psi(i, j));
      int segEnd = norm_seg(m, j - delta(j));
      return get_rel_from_bRels(segStart, segEnd, RELA, m);
    }

  }

  return Rel();
}

Rel b_com_iii(B_rel r1, B_rel r2, B_rel r3) {

  int m = r1.getM();
  int i = r1.getSeg();
  int j = r2.getSeg();
  int k = r3.getSeg();
  int gap = j + k;
  Rel r2_prime = omega(j, k, gap, INTR, m);
  vector<B_rel> bRels = r2_prime.getBRels();
  Rel result_in_a;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    result_in_a = cup(result_in_a, b_com_aaa(B_rel(ABSO, i, m), (*it)));
  }
  // change bRels from ABSO to INTR
  vector<B_rel> bRels_in_a = result_in_a.getBRels();
  vector<B_rel> bRels_in_i;

  for (auto it = bRels_in_a.begin(); it != bRels_in_a.end(); it++) {
    bRels_in_i.push_back(B_rel(INTR, (*it).getSeg(), m));
  }

  return Rel(INTR, m, bRels_in_i);
}

Rel b_com_aai(B_rel r1, B_rel r2, B_rel r3) {
  Rel result_in_a = b_com_aaa(r1, r2);
  vector<B_rel> bRels = result_in_a.getBRels();

  Rel result;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    // based on Rule 1 of Proposition 5.
    result = cup(result, b_com_tau((*it), r3, AI));
  }

  return result;
}

Rel b_com_iaa(B_rel r1, B_rel r2, B_rel r3) {
  // from I_ab_i to A_ab_i' based on Rule 2 of Proposition 5.
  Rel r1_prime = b_com_tau(r1, r3, IA);
  vector<B_rel> bRels = r1_prime.getBRels();

  Rel result;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    result = cup(result, b_com_aaa((*it), r2));
  }

  return result;
}

Rel b_com_aia(B_rel r1, B_rel r2, B_rel r3) {
  // from I_bc_j to A_bc_j' based on Rule 2 of Proposition 5.
  Rel r2_prime = b_com_tau(r2, r3, IA);
  vector<B_rel> bRels = r2_prime.getBRels();

  Rel result;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    result = cup(result, b_com_aaa(r1, (*it)));
  }

  return result;
}

Rel b_com_aii(B_rel r1, B_rel r2, B_rel r3, B_rel r4) {
  // from I_bc_j to A_bc_j' based on Rule 2 of Proposition 5.
  Rel r2_prime = b_com_tau(r2, r3, IA);
  vector<B_rel> bRels = r2_prime.getBRels();

  Rel result_in_a;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    result_in_a = cup(result_in_a, b_com_aaa(r1, (*it)));
  }

  vector<B_rel> bRels_in_a = result_in_a.getBRels();
  Rel result_in_i;

  for (auto it = bRels_in_a.begin(); it != bRels_in_a.end(); it++) {
    result_in_i = cup(result_in_i, b_com_tau((*it), r4, AI));
  }

  return result_in_i;
}

Rel b_com_iia(B_rel r1, B_rel r2, B_rel r3, B_rel r4) {
  Rel r1_prime = b_com_tau(r1, r3, IA);
  Rel r2_prime = b_com_tau(r2, r4, IA);
  vector<B_rel> r1_bRels = r1_prime.getBRels();
  vector<B_rel> r2_bRels = r2_prime.getBRels();
  Rel result;

  for (auto it_1 = r1_bRels.begin(); it_1 != r1_bRels.end(); it_1++) {
    for (auto it_2 = r2_bRels.begin(); it_2 != r2_bRels.end(); it_2++) {
      result = cup(result, b_com_aaa((*it_1), (*it_2)));
    }
  }

  return result;
}

Rel b_com_iai(B_rel r1, B_rel r2, B_rel r3, B_rel r4) {
  Rel r1_prime = b_com_tau(r1, r3, IA);
  // Rel r2_prime = b_com_tau(r2, r4, IA);
  vector<B_rel> bRels = r1_prime.getBRels();
  // vector<B_rel> r2_bRels = r2_prime.getBRels();
  Rel result_in_a;

  for (auto it = bRels.begin(); it != bRels.end(); it++) {
    result_in_a = cup(result_in_a, b_com_aaa((*it), r2));
  }

  vector<B_rel> bRels_in_a = result_in_a.getBRels();
  Rel result_in_i;

  for (auto it = bRels_in_a.begin(); it != bRels_in_a.end(); it++) {
    result_in_i = cup(result_in_i, b_com_tau((*it), r4, AI));
  }

  return result_in_i;
}

Rel b_com_iir(B_rel r1, B_rel r2, B_rel r3, B_rel r4) {
  Rel r1_prime = b_com_tau(r1, r3, IA);
  Rel r2_prime = b_com_tau(r2, r4, IA);
  vector<B_rel> r1_bRels = r1_prime.getBRels();
  vector<B_rel> r2_bRels = r2_prime.getBRels();
  Rel result;

  for (auto it_1 = r1_bRels.begin(); it_1 != r1_bRels.end(); it_1++) {
    for (auto it_2 = r2_bRels.begin(); it_2 != r2_bRels.end(); it_2++) {
      result = cup(result, b_com_aar((*it_1), (*it_2)));
    }
  }

  return result;
}

Rel b_com(B_rel r1, B_rel r2, B_rel r3, B_rel r4, com_type type) {

  if (type == AII) {
    return b_com_aii(r1, r2, r3, r4);
  }

  if (type == IIA) {
    return b_com_iia(r1, r2, r3, r4);
  }

  if (type == IAI) {
    return b_com_iai(r1, r2, r3, r4);
  }

  if (type == IIR) {
    return b_com_iir(r1, r2, r3, r4);
  }

  return Rel();
}

Rel b_com(B_rel r1, B_rel r2, B_rel r3, com_type type) {
  if (r1.getM() != r2.getM() || r2.getM() != r3.getM() ||
    r1.getM() != r3.getM()) {

    return Rel();
  }

  if (type == III) {
    return b_com_iii(r1, r2, r3);
  }

  if (type == AIA) {
    return b_com_aia(r1, r2, r3);
  }

  if (type == AAI) {
    return b_com_aai(r1, r2, r3);
  }

  if (type == IAA) {
    return b_com_iaa(r1, r2, r3);
  }

  return Rel();
}

Rel b_com(B_rel r1, B_rel r2, com_type type) {
  if (r1.getM() != r2.getM()) {
    return Rel();
  }

  if (type == AAA) {
    return b_com_aaa(r1, r2);
  }

  if (type == AAR) {
    return b_com_aar(r1, r2);
  }

  if (type == ARA) {
    return b_com_ara(r1, r2);
  }

  if (type == RAA) {
    return b_com_raa(r1, r2);
  }

  if (type == IRI) {
    return b_com_iri(r1, r2);
  }

  if (type == RII) {
    return b_com_rii(r1, r2);
  }

  if (type == RRA) {
    return Rel(ABSO, r1.getM(), true);
  }

  if (type == RRI) {
    return Rel(INTR, r1.getM(), true);
  }

  if (type == ARR || type == RAR || type == IRR || type == RIR) {
    return Rel(RELA, r1.getM(), true);
  }

  if (type == P) {
    return b_com_phi(r1, r2);
  }

  if (type == P_i) {
    return b_com_phi_infer(r1, r2);
  }

  return Rel();
}

Rel b_com(B_rel r1, B_rel r2, com_type type, com_sub_type sub_type) {
  if (r1.getM() != r2.getM()) {
    return Rel();
  }

  if (type == Tau) { // direction relation translation
    return b_com_tau(r1, r2, sub_type);
  }

  if (type == RRR) {
    return b_com_rrr(r1, r2, sub_type);
  }

  return Rel();
}
