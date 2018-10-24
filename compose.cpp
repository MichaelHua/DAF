#include <iostream>
using namespace std;

#include "global.h"
#include "b_rel.h"
#include "rel.h"
#include "rel_util.h"
#include "b_com.h"

Rel apply_b_com(Rel (*fun)(B_rel, B_rel), B_rel r1, B_rel r2) {
  return (*fun)(r1, r2);
}

Rel apply_b_com(Rel (*fun)(B_rel, B_rel, B_rel), B_rel r1, B_rel r2, B_rel r3) {
  return (*fun)(r1, r2, r3);
}

Rel apply_b_com(Rel (*fun)(B_rel, B_rel, B_rel, B_rel), B_rel r1, B_rel r2,
  B_rel r3, B_rel r4) {
  return (*fun)(r1, r2, r3, r4);
}

Rel apply_b_com(Rel (*fun)(B_rel, B_rel, com_sub_type), B_rel r1, B_rel r2,
  com_sub_type sub_type) {
  return (*fun)(r1, r2, sub_type);
}

Rel compose(Rel r1, Rel r2, Rel r3, Rel r4, com_type type) {

  vector<B_rel> r1_bRels = r1.getBRels();
  vector<B_rel> r2_bRels = r2.getBRels();
  vector<B_rel> r3_bRels = r3.getBRels();
  vector<B_rel> r4_bRels = r4.getBRels();

  Rel result;

  // cup pairs of b_rels
  for (auto it_1 = r1_bRels.begin(); it_1 != r1_bRels.end(); it_1++) {
    B_rel r1_bRel = *it_1;

    for (auto it_2 = r2_bRels.begin(); it_2 != r2_bRels.end(); it_2++) {
      B_rel r2_bRel = *it_2;

      for (auto it_3 = r3_bRels.begin(); it_3 != r3_bRels.end(); it_3++) {
        B_rel r3_bRel = *it_3;

        for (auto it_4 = r4_bRels.begin(); it_4 != r4_bRels.end(); it_4++) {
          B_rel r4_bRel = *it_4;


          if (type == AII) {
            result = cup(result, apply_b_com(b_com_aii,
              r1_bRel, r2_bRel, r3_bRel, r4_bRel));
          }

          if (type == IIA) {
            result = cup(result, apply_b_com(b_com_iia,
              r1_bRel, r2_bRel, r3_bRel, r4_bRel));
          }

          if (type == IAI) {
            result = cup(result, apply_b_com(b_com_iai,
              r1_bRel, r2_bRel, r3_bRel, r4_bRel));
          }

          if (type == IIR) {
            result = cup(result, apply_b_com(b_com_iir,
              r1_bRel, r2_bRel, r3_bRel, r4_bRel));
          }

        }
      }
    }
  }

  return result;
}

Rel compose(Rel r1, Rel r2, Rel r3, com_type type) {
  if (r1.getM() != r2.getM() || r2.getM() != r3.getM() ||
    r1.getM() != r3.getM()) {

    return Rel();
  }

  vector<B_rel> r1_bRels = r1.getBRels();
  vector<B_rel> r2_bRels = r2.getBRels();
  vector<B_rel> r3_bRels = r3.getBRels();

  Rel result;

  // cup pairs of b_rels
  for (auto it_1 = r1_bRels.begin(); it_1 != r1_bRels.end(); it_1++) {
    B_rel r1_bRel = *it_1;

    for (auto it_2 = r2_bRels.begin(); it_2 != r2_bRels.end(); it_2++) {
      B_rel r2_bRel = *it_2;

      for (auto it_3 = r3_bRels.begin(); it_3 != r3_bRels.end(); it_3++) {
        B_rel r3_bRel = *it_3;


        if (type == III) {
          result = cup(result, apply_b_com(b_com_iii, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == AIA) {
          result = cup(result, apply_b_com(b_com_aia, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == AAI) {
          result = cup(result, apply_b_com(b_com_aai, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == IAA) {
          result = cup(result, apply_b_com(b_com_iaa, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == AIR) {
          result = cup(result, apply_b_com(b_com_air, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == ARI) {
          result = cup(result, apply_b_com(b_com_ari, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == IAR) {
          result = cup(result, apply_b_com(b_com_iar, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == IRA) {
          result = cup(result, apply_b_com(b_com_ira, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == RAI) {
          result = cup(result, apply_b_com(b_com_rai, r1_bRel, r2_bRel, r3_bRel));
        }

        if (type == RIA) {
          result = cup(result, apply_b_com(b_com_ria, r1_bRel, r2_bRel, r3_bRel));
        }
      }
    }
  }

  return result;
}

Rel compose(Rel r1, Rel r2, com_type type) {
  if (r1.getM() != r2.getM()) {
    return Rel();
  }

  // non-informative across-category compositions
  if (type == RRA) {
    return Rel(ABSO, r1.getM(), true);
  }

  if (type == RRI) {
    return Rel(INTR, r1.getM(), true);
  }

  if (type == ARR || type == RAR || type == IRR || type == RIR) {
    return Rel(RELA, r1.getM(), true);
  }

  // other cases
  vector<B_rel> r1_bRels = r1.getBRels();
  vector<B_rel> r2_bRels = r2.getBRels();

  Rel result;

  // cup pairs of b_rels
  for (auto it_1 = r1_bRels.begin(); it_1 != r1_bRels.end(); it_1++) {
    B_rel r1_bRel = *it_1;

    for (auto it_2 = r2_bRels.begin(); it_2 != r2_bRels.end(); it_2++) {
      B_rel r2_bRel = *it_2;

      if (type == AAA) {
        result = cup(result, apply_b_com(b_com_aaa, r1_bRel, r2_bRel));
      }

      if (type == AAR) {
        result = cup(result, apply_b_com(b_com_aar, r1_bRel, r2_bRel));
      }

      if (type == ARA) {
        result = cup(result, apply_b_com(b_com_ara, r1_bRel, r2_bRel));
      }

      if (type == RAA) {
        result = cup(result, apply_b_com(b_com_raa, r1_bRel, r2_bRel));
      }

      if (type == IRI) {
        result = cup(result, apply_b_com(b_com_iri, r1_bRel, r2_bRel));
      }

      if (type == RII) {
        result = cup(result, apply_b_com(b_com_rii, r1_bRel, r2_bRel));
      }

      if (type == P) {
        result = cup(result, apply_b_com(b_com_phi, r1_bRel, r2_bRel));
      }

      if (type == P_i) {
        result = cup(result, apply_b_com(b_com_phi_infer, r1_bRel, r2_bRel));
      }

    }
  }

  return result;
}

Rel compose(Rel r1, Rel r2, com_type type, com_sub_type sub_type) {
  if (r1.getM() != r2.getM()) {
    return Rel();
  }

  // other cases
  vector<B_rel> r1_bRels = r1.getBRels();
  vector<B_rel> r2_bRels = r2.getBRels();

  Rel result;

  // cup pairs of b_rels
  for (auto it_1 = r1_bRels.begin(); it_1 != r1_bRels.end(); it_1++) {
    B_rel r1_bRel = *it_1;

    for (auto it_2 = r2_bRels.begin(); it_2 != r2_bRels.end(); it_2++) {
      B_rel r2_bRel = *it_2;

      if (type == Tau) {
        result = cup(result, apply_b_com(b_com_tau, r1_bRel,
          r2_bRel, sub_type));
      }

      if (type == RRR) {
        result = cup(result, apply_b_com(b_com_rrr, r1_bRel,
          r2_bRel, sub_type));
      }
    }
  }

  return result;
}
