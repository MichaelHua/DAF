#include <iostream>
#include <math.h>
#include <set>

#include "qualifier.h"
#include "ori_point.h"
#include "daf.h"
#include "b_rel.h"
#include "global.h"
#include "rel.h"
#include "converse.h"
#include "compose.h"
#include "rel_util.h"
#include "b_com.h"
#include "rels_for_test.h"

#include "cmdparser.hpp"
#include "cmdconfig.h"


using namespace std;

/*
******************************* TO-DOs **********************************
1. Start DAF-m Qualification. (Copied from OPRA first)

1.1 Basic Relations (only Absolute Relations and Binary Same Relations).

1.2 Add Anchor Relations.
1.3 Add Intrinsic Relations.
1.4 Add Ternary. Relative Relations and Ternary Same Relations.

DONE Any problem with normalisation?
DONE But problematic when there are rounding errors...
DONE Function tests...
DONE (in daf.cpp) generate basic relations

2. DAF-m Converse from OPRA converse?
DONE refactor daf_qualifier with new basic relations and rel_cate

DONE a seperate file for converse operations of baisc and non-basic rels....

3. DAF-m Composition from OPRA composition?

DONE // different types of composition operations
enum com_type {
  DONE Tau, // direction relation translation
  DONE AAA, III, RRR, // in-category composition
  DONE AAR, ARA, RAA, IRI, RII, // trans-independent across-category
  DONE AIA, AII, AAI, IIA, IAA, IAI, IIR, // trans-dependent across-category
  TODO AIR, ARI, IAR, IRA, RAI, RIA // trans-dependent across-category
  DONE RRA, ARR, RAR, RRI, IRR, RIR, // non-informative
  Phi
};

4. Operations between composite relations
DONE set operations
DONE converse and compose
DONE tests

5. DONE Command line input (if too complicated in the future I can use boost)
now just keep it simple. Also you can refer to the dsitributed system
project code.

6. DONE At least you can run the case study (hare shooting).
******************************* TO-DOs **********************************


************************ Potential TO-DOs ***************************
how to deal with unknown anchors or positions?

file input?

how to prove my rules are correct? combined with Qualification? Manually
check the results? How to prove my rules are correct?

error handling? check whether inputs are valid? At least you should check
whether relation types match the composition type.

For qualification Interval input... rather than exact points...
e.g. x ([1,2], [2,3], 0). In other words, results are rels rather than b_rels.
Check how SparQ does with this problem?

check the logic and process of norm_seg?

Before uploading to Github, refactor the structure of this project
so that it is more readable?
************************ Potential TO-DOs ***************************

*/


void print_result(string expected, string result) {
  cout << expected << " ----> " << result << endl;
}

void print_result(string expected, float result) {
  cout << expected << " ----> " << result << endl;
}

void print_result(string expected, int result) {
  cout << expected << " ----> " << result << endl;
}

void print_result(string result) {
  cout << "----> " << result << endl;
}

void print_line_break(string title) {
  cout << endl << "*********** " << title << " *************" << endl << endl;
}

void print_line_break(void) {
  cout << endl << "******************************************" << endl << endl;
}

void rel_test(void) {
  int m = 4;
  Rel rel;

  print_result("0", rel.getCate());
  print_result("-1", rel.getM());
  print_result(rel.getStr());

  rel = Rel(ABSO, m);
  print_result("2", rel.getCate());
  print_result("4", rel.getM());
  print_result(rel.getStr());

  vector<B_rel> bRels;
  for (int i = 0; i < 8; i++) {
    bRels.push_back(B_rel(ABSO, i, m));
  }
  rel = Rel(ABSO, m, bRels);
  print_result("rel_1", rel.getStr());

  vector<B_rel> bRels_2;
  for (int i = 7; i >= 0; i--) {
    bRels_2.push_back(B_rel(ABSO, i, m));
  }
  Rel rel_2(ABSO, m, bRels_2);
  print_result("rel_2", rel_2.getStr());
  print_result("1", rel_2.isEqual(rel));

  vector<B_rel> bRels_3;
  for (int i = 6; i >= 0; i--) {
    bRels_3.push_back(B_rel(ABSO, i, m));
  }
  bRels_3.push_back(A_9);
  Rel rel_3(ABSO, m, bRels_3);
  print_result("rel_3", rel_3.getStr());
  print_result("0", rel_3.isEqual(rel));

  vector<B_rel> bRels_U;
  for (int i = 0; i < 4 * m; i++) {
    bRels_U.push_back(B_rel(ABSO, i, m));
  }
  Rel rel_U(ABSO, m, bRels_U);
  print_result("A_U", rel_U.getStr());
  print_result("0", rel_U.isEqual(rel));


  print_line_break();
}

void b_con_test(void) {

  int m = 4;

  print_result("E", converse(r_e).getStr());
  print_result("S_2", converse(S_2).getStr());
  print_result("S_12", converse(S_12, INV).getStr());
  print_result("S_13", converse(S_12, SC).getStr());
  print_result("S_23", converse(S_12, SCI).getStr());
  print_result("S_13", converse(S_12, HM).getStr());
  print_result("S_23", converse(S_12, HMI).getStr());
  print_result("S_23", converse(S_13, INV).getStr());
  print_result("S_13", converse(S_23, INV).getStr());
  print_result("S_3", converse(S_3, INV).getStr());
  print_result("S_3", converse(S_3, SC).getStr());

  print_result("A_8", converse(A_0).getStr());
  print_result("A_0", converse(A_8).getStr());
  print_result("A_6", converse(A_14).getStr());
  print_result("A_6", converse(A_30).getStr());
  print_result("A_1", converse(A_9).getStr());

  print_result("Phi_0", converse(P_0).getStr());
  print_result("Phi_8", converse(P_8).getStr());
  print_result("Phi_2", converse(P_14).getStr());
  print_result("Phi_2", converse(P_30).getStr());
  print_result("Phi_7", converse(P_9).getStr());

  print_line_break();

  print_result("I_8", converse(I_0, P_0).getStr());
  print_result("I_0", converse(I_8, P_0).getStr());
  print_result("I_6", converse(I_14, P_0).getStr());
  print_result("I_6", converse(I_30, P_0).getStr());
  print_result("I_1", converse(I_9, P_0).getStr());

  print_line_break();

  print_result("I_7", converse(I_0, P_1).getStr());
  print_result("I_15", converse(I_8, P_1).getStr());
  print_result("I_5", converse(I_14, P_1).getStr());
  print_result("I_5", converse(I_30, P_1).getStr());
  print_result("I_0,1,15", converse(I_9, P_1).getStr());

  print_line_break();

  B_rel anhr(PHI, 4 * m + 1, m);
  print_result("I_7", converse(I_0, anhr).getStr());
  print_result("I_15", converse(I_8, anhr).getStr());
  print_result("I_5", converse(I_14, anhr).getStr());
  print_result("I_5", converse(I_30, anhr).getStr());
  print_result("I_0,1,15", converse(I_9, anhr).getStr());

  print_line_break();

  print_result("R_7", converse(R_n_1, INV).getStr());
  print_result("R_8", converse(R_0, INV).getStr());
  print_result("R_9", converse(R_1, INV).getStr());
  print_result("R_9", converse(R_2, INV).getStr());
  print_result("R_9-11", converse(R_3, INV).getStr());
  print_result("R_9-11", converse(R_4, INV).getStr());
  print_result("R_9-13", converse(R_5, INV).getStr());
  print_result("R_9-13", converse(R_6, INV).getStr());
  print_result("R_9-15", converse(R_7, INV).getStr());
  print_result("R_0,8", converse(R_8, INV).getStr());
  print_result("R_1-7", converse(R_9, INV).getStr());
  print_result("R_3-7", converse(R_10, INV).getStr());
  print_result("R_3-7", converse(R_11, INV).getStr());
  print_result("R_5-7", converse(R_12, INV).getStr());
  print_result("R_5-7", converse(R_13, INV).getStr());
  print_result("R_7", converse(R_14, INV).getStr());
  print_result("R_7", converse(R_15, INV).getStr());
  print_result("R_8", converse(R_16, INV).getStr());
  print_result("R_9", converse(R_17, INV).getStr());

  print_line_break();

  print_result("R_8", converse(R_0, SC).getStr());
  print_result("R_0,8", converse(R_8, SC).getStr());
  print_result("R_9-15", converse(R_7, SC).getStr());
  print_result("R_1-7", converse(R_9, SC).getStr());
  print_result("R_7", converse(R_n_1, SC).getStr());
  print_result("R_9", converse(R_17, SC).getStr());

  print_line_break();

  print_result("R_8", converse(R_0, SCI).getStr());
  print_result("R_0,8", converse(R_8, SCI).getStr());
  print_result("R_1-7", converse(R_7, SCI).getStr());
  print_result("R_9-15", converse(R_9, SCI).getStr());
  print_result("R_9", converse(R_n_1, SCI).getStr());
  print_result("R_7", converse(R_17, SCI).getStr());

  print_line_break();

  print_result("R_8", converse(R_0, HM).getStr());
  print_result("R_0,8", converse(R_8, HM).getStr());
  print_result("R_1-7", converse(R_7, HM).getStr());
  print_result("R_9-15", converse(R_9, HM).getStr());
  print_result("R_9", converse(R_n_1, HM).getStr());
  print_result("R_7", converse(R_17, HM).getStr());

  print_line_break();

  print_result("R_0", converse(R_0, HMI).getStr());
  print_result("R_8", converse(R_8, HMI).getStr());
  print_result("R_9", converse(R_7, HMI).getStr());
  print_result("R_7", converse(R_9, HMI).getStr());
  print_result("R_1", converse(R_n_1, HMI).getStr());
  print_result("R_15", converse(R_17, HMI).getStr());

  print_line_break();
}

void con_test() {
  // tests of composite relations
  print_result("_", converse(r_A_0).getStr());
  print_result("_", converse(r_A_0_to_1).getStr());
  print_result("_", converse(r_A_1_to_2).getStr());
  print_result("_", converse(r_A_0_to_2).getStr());
  print_result("_", converse(r_A_0_to_5).getStr());
  print_result("_", converse(r_A_5_to_9).getStr());
  print_result("_", converse(r_A_15_to_1).getStr());
  print_result("_", converse(r_A_0_5).getStr());

  print_result("_", converse(r_P_0_to_1).getStr());
  print_result("_", converse(r_P_15_to_1).getStr());
  print_result("_", converse(r_P_0_5).getStr());

  print_line_break();

  print_result("_", converse(r_I_0, r_P_0).getStr());
  print_result("_", converse(r_I_0_to_1, r_P_0_to_1).getStr());
  print_result("_", converse(r_I_1_to_2, r_P_1_to_2).getStr());
  print_result("_", converse(r_I_0_to_2, r_P_0_to_2).getStr());
  print_result("_", converse(r_I_0_to_5, r_P_0_to_5).getStr());
  print_result("_", converse(r_I_5_to_9, r_P_5_to_9).getStr());
  print_result("_", converse(r_I_0_5, r_P_0_5).getStr());
  print_result("_", converse(r_I_15_to_1, r_P_15_to_1).getStr());

  print_line_break();
  print_result("_", converse(r_R_0_to_1, INV).getStr());
  print_result("_", converse(r_R_0_to_1, SC).getStr());
  print_result("_", converse(r_R_0_to_1, SCI).getStr());
  print_result("_", converse(r_R_0_to_1, HM).getStr());
  print_result("_", converse(r_R_0_to_1, HMI).getStr());
  print_result("_", converse(r_R_15_to_1, INV).getStr());
  print_result("_", converse(r_R_15_to_1, SC).getStr());
  print_result("_", converse(r_R_15_to_1, SCI).getStr());
  print_result("_", converse(r_R_15_to_1, HM).getStr());
  print_result("_", converse(r_R_15_to_1, HMI).getStr());

}

void samepos_test(void) {

  OriPoint sp1(1, 0, 0.0);
  OriPoint sp2(1, 1, 0.0);
  OriPoint sp3(0, 1, 0.0);
  OriPoint sp4(1, 0, M_PI);
  OriPoint sp5(1, 1, M_PI);
  OriPoint sp6(1, 1, M_PI);
  int m = 4;

  print_result("E", getRel(m, SAMPOS, sp1, sp2).getStr());
  print_result("E", getRel(m, SAMPOS, sp1, sp2, sp3).getStr());
  print_result("S_2", getRel(m, SAMPOS, sp1, sp4).getStr());
  print_result("S_13", getRel(m, SAMPOS, sp1, sp3, sp4).getStr());
  print_result("S_12",getRel(m, SAMPOS, sp1, sp4, sp3).getStr());
  print_result("S_23", getRel(m, SAMPOS, sp1, sp5, sp6).getStr());
  print_result("S_3", getRel(m, SAMPOS, sp2, sp5, sp6).getStr());

}

void norm_seg_test(void) {
  print_result("0", norm_seg(2, 0));
  print_result("7", norm_seg(2, 7));
  print_result("0", norm_seg(2, 8));
  print_result("2", norm_seg(2, 26));
  print_result("7", norm_seg(2, -1));
  print_result("6", norm_seg(2, -26));
  print_result("10", norm_seg(4, 26));
  print_result("6", norm_seg(4, -26));
}

void bRels_test() {
  Daf daf_4(4);
  Daf daf_2(2);
  print_result(daf_2.getBRelsStr());
  Daf daf_8(8);

  int m = 4;
  B_rel r1;
  B_rel r2(ABSO, 2, m);
  B_rel r3(INTR, 2, m);
  B_rel r4(ABSO, 2, m);
  B_rel r5(ABSO, 3, m);
  B_rel S_12(SAMPOS, 12);

  print_result("0", r2 < r4);
  print_result("1", r2 < r5);

  print_result(r1.getStr());
  print_result(r2.getStr());
  print_result(r3.getStr());
  print_result(r4.getStr());
  print_result(S_12.getStr());

  print_result("1", r1.isEmpty());
  print_result("0", r1.isEqual(r2));
  print_result("0", r2.isEmpty());
  print_result("0", r2.isEqual(r3));
  print_result("1", r2.isEqual(r4));
  print_result("0", r2.isEqual(r5));

}

void getRel_test() {
  OriPoint opA(1, 0, 0.0);
  OriPoint opB(1, 1, 0.0);
  OriPoint opC(0, 1, 0.0);
  OriPoint opOrigin(0, 0, 0.0);
  int m = 4; // granularity
  float tiny = 0.00001; // precision guranteed with 1e-5. Not with 1e-6.

  print_result("A_0", getRel(m, ABSO, opA, opB).getStr());
  print_result("A_8", getRel(m, ABSO, opB, opA).getStr());
  print_result("A_2", getRel(m, ABSO, opA, opC).getStr());
  print_result("A_10", getRel(m, ABSO, opC, opA).getStr());
  print_result("A_4", getRel(m, ABSO, opB, opC).getStr());
  print_result("A_12", getRel(m, ABSO, opC, opB).getStr());

  print_result("A_12", getRel(m, ABSO, opOrigin, opA).getStr());
  print_result("A_14", getRel(m, ABSO, opOrigin, opB).getStr());
  print_result("A_0", getRel(m, ABSO, opOrigin, opC).getStr());
  print_result("A_4", getRel(m, ABSO, opA, opOrigin).getStr());
  print_result("A_6", getRel(m, ABSO, opB, opOrigin).getStr());
  print_result("A_8", getRel(m, ABSO, opC, opOrigin).getStr());

  float delta = M_PI / 4 - tiny;
  opA.rotateANCHOR(delta);
  opOrigin.rotateANCHOR(delta);

  print_result("I_15", getRel(m, INTR, opA, opB).getStr());
  print_result("I_8", getRel(m, INTR, opB, opA).getStr());
  print_result("I_1", getRel(m, INTR, opA, opC).getStr());
  print_result("I_10", getRel(m, INTR, opC, opA).getStr());
  print_result("I_4", getRel(m, INTR, opB, opC).getStr());
  print_result("I_12", getRel(m, INTR, opC, opB).getStr());

  print_result("I_11", getRel(m, INTR, opOrigin, opA).getStr());
  print_result("I_13", getRel(m, INTR, opOrigin, opB).getStr());
  print_result("I_15", getRel(m, INTR, opOrigin, opC).getStr());
  print_result("I_3", getRel(m, INTR, opA, opOrigin).getStr());
  print_result("I_6", getRel(m, INTR, opB, opOrigin).getStr());
  print_result("I_8", getRel(m, INTR, opC, opOrigin).getStr());

  print_result("R_4", getRel(m, RELA, opA, opB, opC).getStr());
  print_result("R_10", getRel(m, RELA, opA, opC, opB).getStr());
  print_result("R_10", getRel(m, RELA, opB, opA, opC).getStr());
  print_result("R_6", getRel(m, RELA, opB, opC, opA).getStr());
  print_result("R_6", getRel(m, RELA, opC, opA, opB).getStr());
  print_result("R_12", getRel(m, RELA, opC, opB, opA).getStr());

  print_result("Phi_15", getRel(m, PHI, opA, opB).getStr());
  print_result("Phi_1", getRel(m, PHI, opB, opA).getStr());
  print_result("Phi_15", getRel(m, PHI, opA, opC).getStr());
  print_result("Phi_1", getRel(m, PHI, opC, opA).getStr());
  print_result("Phi_0", getRel(m, PHI, opB, opC).getStr());
  print_result("Phi_0", getRel(m, PHI, opC, opB).getStr());

}

void rounding_error_test() {
  int very_tiny = 0.000001;
  int m = 4;
  print_result("9 and an expected error", calOriSeg(m, M_PI + very_tiny));
  print_result("7 and an expected error", calOriSeg(m, M_PI - very_tiny));
}

void calOriSeg_test() {
  float tiny = 0.00001;
  int m = 2;

  print_result("7", calOriSeg(m, 0 - tiny));
  print_result("0", calOriSeg(m, 0));
  print_result("1", calOriSeg(m, 0 + tiny));

  print_result("1", calOriSeg(m, M_PI / 4 - tiny));
  print_result("1", calOriSeg(m, M_PI / 4));
  print_result("1", calOriSeg(m, M_PI / 4 + tiny));

  print_result("1", calOriSeg(m, M_PI / 2 - tiny));
  print_result("2", calOriSeg(m, M_PI / 2));
  print_result("3", calOriSeg(m, M_PI / 2 + tiny));

  print_result("3", calOriSeg(m, M_PI * 3 / 4 - tiny));
  print_result("3", calOriSeg(m, M_PI * 3 / 4));
  print_result("3", calOriSeg(m, M_PI * 3 / 4 + tiny));

  print_result("3", calOriSeg(m, M_PI - tiny));
  print_result("4", calOriSeg(m, M_PI));
  print_result("5", calOriSeg(m, M_PI + tiny));

  print_result("7", calOriSeg(m, 2 * M_PI - tiny));
  print_result("0", calOriSeg(m, 2 * M_PI));
  print_result("1", calOriSeg(m, 2 * M_PI + tiny));

  print_line_break();

  m = 4;
  print_result("15", calOriSeg(m, 0 - tiny));
  print_result("0", calOriSeg(m, 0));
  print_result("1", calOriSeg(m, 0 + tiny));

  print_result("1", calOriSeg(m, M_PI / 4 - tiny));
  print_result("2", calOriSeg(m, M_PI / 4));
  print_result("3", calOriSeg(m, M_PI / 4 + tiny));

  print_result("3", calOriSeg(m, M_PI / 2 - tiny));
  print_result("4", calOriSeg(m, M_PI / 2));
  print_result("5", calOriSeg(m, M_PI / 2 + tiny));

  print_result("5", calOriSeg(m, M_PI * 3 / 4 - tiny));
  print_result("6", calOriSeg(m, M_PI * 3 / 4));
  print_result("7", calOriSeg(m, M_PI * 3 / 4 + tiny));

  print_result("7", calOriSeg(m, M_PI - tiny));
  print_result("8", calOriSeg(m, M_PI));
  print_result("9", calOriSeg(m, M_PI + tiny));

  print_result("15", calOriSeg(m, 2 * M_PI - tiny));
  print_result("0", calOriSeg(m, 2 * M_PI));
  print_result("1", calOriSeg(m, 2 * M_PI + tiny));
}

void norm_test() {
  float tiny = 0.00001;
  OriPoint opD(0, 1, 2 * M_PI);
  print_result("0", opD.getANCHOR());
  opD.setANCHOR(- 2 * M_PI);
  print_result("0", opD.getANCHOR());

  float huge = 2 * M_PI - tiny;

  opD.rotateANCHOR(tiny);
  print_result(to_string(tiny), opD.getANCHOR());
  opD.rotateANCHOR(-tiny);
  print_result("0", opD.getANCHOR());
  opD.rotateANCHOR(-tiny);
  print_result(to_string(huge), opD.getANCHOR());

  opD.setANCHOR(0);
  opD.rotateANCHOR(2 * M_PI + tiny);
  print_result(to_string(tiny), opD.getANCHOR());
  opD.rotateANCHOR(-2 * M_PI - tiny);
  print_result("0", opD.getANCHOR());


  opD.setANCHOR(0);
  opD.rotateANCHOR(2 * M_PI - tiny);
  print_result(to_string(huge), opD.getANCHOR());
  opD.rotateANCHOR(-2 * M_PI + tiny);
  print_result("0", opD.getANCHOR());

}

void b_com_test() {
  // AAA
  // case 1, 2, 3.
  print_result("A_0", b_com(A_0, A_0, AAA).getStr());
  print_result("A_U", b_com(A_1, A_9, AAA).getStr());
  print_result("A_0,8", b_com(A_0, A_8, AAA).getStr());

  // case 4.
  print_result("_", b_com(A_0, A_1, AAA).getStr());
  print_result("_", b_com(A_0, A_2, AAA).getStr());
  print_result("_", b_com(A_0, A_3, AAA).getStr());
  print_result("_", b_com(A_0, A_4, AAA).getStr());
  print_result("_", b_com(A_0, A_5, AAA).getStr());
  print_result("_", b_com(A_0, A_6, AAA).getStr());
  print_result("_", b_com(A_0, A_7, AAA).getStr());

  // case 5.
  print_result("_", b_com(A_0, A_9, AAA).getStr());
  print_result("_", b_com(A_0, A_10, AAA).getStr());
  print_result("_", b_com(A_0, A_11, AAA).getStr());
  print_result("_", b_com(A_0, A_12, AAA).getStr());
  print_result("_", b_com(A_0, A_13, AAA).getStr());
  print_result("_", b_com(A_0, A_14, AAA).getStr());
  print_result("_", b_com(A_0, A_15, AAA).getStr());

  // norm test
  print_result("_", b_com(A_0, A_16, AAA).getStr());
  print_result("_", b_com(A_0, A_17, AAA).getStr());
  print_result("_", b_com(A_0, A_n_1, AAA).getStr());

  print_line_break();

  // Tau tests
  print_result("_", b_com(A_0, P_1, Tau, AI).getStr());
  print_result("_", b_com(A_1, P_3, Tau, AI).getStr());
  print_result("_", b_com(R_0, P_1, Tau, RI).getStr());
  print_result("_", b_com(R_1, P_3, Tau, RI).getStr());
  print_result("_", b_com(I_0, P_1, Tau, II).getStr());
  print_result("_", b_com(I_1, P_3, Tau, II).getStr());

  print_result("_", b_com(A_0, P_1, Tau, AR).getStr());
  print_result("_", b_com(A_1, P_3, Tau, AR).getStr());
  print_result("_", b_com(R_0, P_1, Tau, RA).getStr());
  print_result("_", b_com(R_1, P_3, Tau, RA).getStr());
  print_result("_", b_com(I_0, P_1, Tau, IA).getStr());
  print_result("_", b_com(I_1, P_3, Tau, IA).getStr());
  print_result("_", b_com(I_0, P_1, Tau, IR).getStr());
  print_result("_", b_com(I_1, P_3, Tau, IR).getStr());

  print_line_break();

  // III tests
  print_result("_", b_com(I_0, I_0, P_0, III).getStr());
  print_result("_", b_com(I_8, I_4, P_4, III).getStr());
  print_result("_", b_com(I_1, I_4, P_5, III).getStr());
  print_result("_", b_com(I_2, I_5, P_5, III).getStr());
  print_result("_", b_com(I_3, I_5, P_5, III).getStr());
  print_result("_", b_com(I_2, I_6, P_5, III).getStr());

  print_line_break();

  // R_31 tests
  print_result("_", b_com(R_3, R_0, RRR, R_31).getStr());
  print_result("_", b_com(R_9, R_8, RRR, R_31).getStr());
  print_result("_", b_com(R_14, R_7, RRR, R_31).getStr());
  print_result("_", b_com(R_14, R_9, RRR, R_31).getStr());

  // R_32 tests
  print_result("_", b_com(R_3, R_0, RRR, R_32).getStr());
  print_result("_", b_com(R_9, R_8, RRR, R_32).getStr());
  print_result("_", b_com(R_14, R_7, RRR, R_32).getStr());
  print_result("_", b_com(R_14, R_9, RRR, R_32).getStr());

  print_result("_", b_com(R_0, R_3, RRR, R_32).getStr());
  print_result("_", b_com(R_8, R_9, RRR, R_32).getStr());
  print_result("_", b_com(R_7, R_14, RRR, R_32).getStr());
  print_result("_", b_com(R_9, R_14, RRR, R_32).getStr());

  print_line_break();

  // translation independent compositions
  print_result("_", b_com(A_1, A_2, AAR).getStr());
  print_result("_", b_com(A_1, A_3, AAR).getStr());

  print_result("_", b_com(A_1, R_2, ARA).getStr());
  print_result("_", b_com(A_1, R_3, ARA).getStr());

  print_result("_", b_com(R_1, A_2, RAA).getStr());
  print_result("_", b_com(R_1, A_3, RAA).getStr());

  print_result("_", b_com(I_1, I_2, IRI).getStr());
  print_result("_", b_com(I_1, R_3, IRI).getStr());

  print_result("_", b_com(R_1, I_2, RII).getStr());
  print_result("_", b_com(R_1, I_3, RII).getStr());

  print_line_break();

  // anchor relation composition
  print_result("_", b_com(P_1, P_2, P).getStr());
  print_result("_", b_com(P_1, P_3, P).getStr());

  // anchor relation inference
  print_result("_", b_com(P_1, P_2, P_i).getStr());
  print_result("_", b_com(P_1, P_3, P_i).getStr());

  print_line_break();

  // translation dependent compositions (one translation)
  print_result("_", b_com(A_1, A_2, P_1, AAI).getStr());
  print_result("_", b_com(A_1, A_2, P_2, AAI).getStr());
  print_result("_", b_com(A_1, A_3, P_1, AAI).getStr());

  print_result("_", b_com(I_1, A_2, P_1, IAA).getStr());
  print_result("_", b_com(I_1, A_2, P_2, IAA).getStr());
  print_result("_", b_com(I_1, A_3, P_1, IAA).getStr());

  print_result("_", b_com(A_1, I_2, P_1, AIA).getStr());
  print_result("_", b_com(A_1, I_2, P_2, AIA).getStr());
  print_result("_", b_com(A_1, I_3, P_1, AIA).getStr());

  print_line_break();

  // translation dependent compositions (two translations)
  print_result("_", b_com(A_1, A_2, P_1, P_1, AII).getStr());
  print_result("_", b_com(A_1, A_2, P_2, P_2, AII).getStr());
  print_result("_", b_com(A_1, A_3, P_1, P_2, AII).getStr());

  print_result("_", b_com(I_1, I_2, P_1, P_1, IIA).getStr());
  print_result("_", b_com(I_1, I_2, P_2, P_2, IIA).getStr());
  print_result("_", b_com(I_1, I_3, P_1, P_2, IIA).getStr());

  print_result("_", b_com(I_1, A_2, P_1, P_1, IAI).getStr());
  print_result("_", b_com(I_1, A_2, P_2, P_2, IAI).getStr());
  print_result("_", b_com(I_1, A_3, P_1, P_2, IAI).getStr());

  print_result("_", b_com(I_1, I_2, P_1, P_1, IIR).getStr());
  print_result("_", b_com(I_1, I_2, P_2, P_2, IIR).getStr());
  print_result("_", b_com(I_1, I_3, P_1, P_2, IIR).getStr());

  print_line_break();
}

void rel_op_test() {
  // cup
  print_result("A_0", cup(r_E, r_A_0).getStr());
  print_result("A_0", cup(r_A_0, r_E).getStr());
  print_result("A_0,1", cup(r_A_0, r_A_1).getStr());
  print_result("A_0,1,2", cup(r_A_0_to_1, r_A_1_to_2).getStr());
  print_result("A_0,1,2", cup(r_A_1_to_2, r_A_0_to_2).getStr());

  // cap
  print_result("E", cap(r_E, r_A_0).getStr());
  print_result("E", cap(r_A_0, r_E).getStr());
  print_result("E", cap(r_A_0, r_A_1).getStr());
  print_result("A_1", cap(r_A_0_to_1, r_A_1_to_2).getStr());
  print_result("A_1,2", cap(r_A_1_to_2, r_A_0_to_2).getStr());
  print_result("A_0,1", cap(r_A_0_to_1, r_A_0_to_2).getStr());

  print_line_break();
}

void com_test() {
  // AAA
  print_result("_", compose(r_A_0, r_A_1, AAA).getStr());
  print_result("_", compose(r_A_0_to_1, r_A_1_to_2, AAA).getStr());
  print_result("_", compose(r_A_1_to_2, r_A_0_to_2, AAA).getStr());
  print_result("_", compose(r_A_0_to_1, r_A_0_to_2, AAA).getStr());
  print_result("_", compose(r_A_0_to_5, r_A_5_to_9, AAA).getStr());
  print_result("_", compose(r_A_0_5, r_A_5_to_9, AAA).getStr());
  print_result("_", compose(r_A_0_to_1, r_A_15_to_1, AAA).getStr());

  print_line_break();

  // Tau tests
  print_result("_", compose(r_A_15_to_1, r_P_15_to_1, Tau, AI).getStr());
  print_result("_", compose(r_A_0_to_2, r_P_0_to_1, Tau, AI).getStr());
  print_result("_", compose(r_R_0_to_2, r_P_15_to_1, Tau, RI).getStr());
  print_result("_", compose(r_R_15_to_1, r_P_0_to_1, Tau, RI).getStr());
  print_result("_", compose(r_I_15_to_1, r_P_15_to_1, Tau, II).getStr());
  print_result("_", compose(r_I_0_to_2, r_P_0_to_1, Tau, II).getStr());

  print_result("_", compose(r_A_15_to_1, r_P_15_to_1, Tau, AR).getStr());
  print_result("_", compose(r_A_0_to_2, r_P_0_to_1, Tau, AR).getStr());
  print_result("_", compose(r_R_0_to_2, r_P_15_to_1, Tau, RA).getStr());
  print_result("_", compose(r_R_15_to_1, r_P_0_to_1, Tau, RA).getStr());
  print_result("_", compose(r_I_15_to_1, r_P_15_to_1, Tau, IA).getStr());
  print_result("_", compose(r_I_0_to_2, r_P_0_to_1, Tau, IA).getStr());
  print_result("_", compose(r_I_15_to_1, r_P_15_to_1, Tau, IR).getStr());
  print_result("_", compose(r_I_0_to_2, r_P_0_to_1, Tau, IR).getStr());

  print_line_break();

  // III tests
  print_result("_", compose(r_I_0_to_1, r_I_0_to_1, r_P_15_to_1, III).getStr());
  print_result("_", compose(r_I_15_to_1, r_I_0_to_1, r_P_0_to_2, III).getStr());
  print_result("_", compose(r_I_0_to_2, r_I_5_to_9, r_P_0_to_2, III).getStr());
  print_result("_", compose(r_I_0_to_2, r_I_1_to_2, r_P_0_to_2, III).getStr());

  print_line_break();

  // R_31 tests
  print_result("_", compose(r_R_0_to_2, r_R_0_to_1, RRR, R_31).getStr());
  print_result("_", compose(r_R_15_to_1, r_R_5_to_9, RRR, R_31).getStr());
  print_result("_", compose(r_R_0_to_5, r_R_1_to_2, RRR, R_31).getStr());
  print_result("_", compose(r_R_0_to_5, r_R_15_to_1, RRR, R_31).getStr());

  // R_32 tests
  print_result("_", compose(r_R_0_to_2, r_R_0_to_1, RRR, R_32).getStr());
  print_result("_", compose(r_R_15_to_1, r_R_5_to_9, RRR, R_32).getStr());
  print_result("_", compose(r_R_0_to_5, r_R_1_to_2, RRR, R_32).getStr());
  print_result("_", compose(r_R_0_to_5, r_R_15_to_1, RRR, R_32).getStr());

  print_result("_", compose(r_R_0_to_1, r_R_0_to_2, RRR, R_32).getStr());
  print_result("_", compose(r_R_5_to_9, r_R_15_to_1, RRR, R_32).getStr());
  print_result("_", compose(r_R_1_to_2, r_R_0_to_5, RRR, R_32).getStr());
  print_result("_", compose(r_R_15_to_1, r_R_0_to_5, RRR, R_32).getStr());

  print_line_break();

  // translation independent compositions
  print_result("_", compose(r_A_15_to_1, r_A_0_to_2, AAR).getStr());
  print_result("_", compose(r_A_15_to_1, r_A_0_to_5, AAR).getStr());

  print_result("_", compose(r_A_15_to_1, r_R_0_to_2, ARA).getStr());
  print_result("_", compose(r_A_15_to_1, r_R_0_to_2, ARA).getStr());

  print_result("_", compose(r_R_0_to_2, r_A_0_to_2, RAA).getStr());
  print_result("_", compose(r_R_0_to_2, r_A_0_to_5, RAA).getStr());

  print_result("_", compose(r_I_15_to_1, r_R_0_to_2, IRI).getStr());
  print_result("_", compose(r_I_15_to_1, r_R_0_to_2, IRI).getStr());

  print_result("_", compose(r_R_0_to_2, r_I_0_to_2, RII).getStr());
  print_result("_", compose(r_R_0_to_2, r_I_1_to_2, RII).getStr());

  print_line_break();

  // anchor relation composition
  print_result("_", compose(r_P_0_to_5, r_P_15_to_1, P).getStr());
  print_result("_", compose(r_P_0_to_5, r_P_0_to_1, P).getStr());

  // anchor relation inference
  print_result("_", compose(r_P_0_to_5, r_P_15_to_1, P_i).getStr());
  print_result("_", compose(r_P_0_to_5, r_P_0_to_1, P_i).getStr());

  print_line_break();

  // translation dependent compositions (one translation)
  print_result("_", compose(r_A_15_to_1, r_A_0_to_2, r_P_0_to_5, AAI).getStr());
  print_result("_", compose(r_A_15_to_1, r_A_0_to_2, r_P_15_to_1, AAI).getStr());
  print_result("_", compose(r_A_15_to_1, r_A_0_to_5, r_P_0_to_5, AAI).getStr());

  print_result("_", compose(r_I_15_to_1, r_A_0_to_2, r_P_0_to_5, IAA).getStr());
  print_result("_", compose(r_I_15_to_1, r_A_0_to_2, r_P_15_to_1, IAA).getStr());
  print_result("_", compose(r_I_15_to_1, r_A_0_to_5, r_P_0_to_5, IAA).getStr());

  print_result("_", compose(r_A_15_to_1, r_I_0_to_2, r_P_0_to_5, AIA).getStr());
  print_result("_", compose(r_A_15_to_1, r_I_0_to_2, r_P_15_to_1, AIA).getStr());
  print_result("_", compose(r_A_15_to_1, r_I_1_to_2, r_P_0_to_5, AIA).getStr());

  print_line_break();

  // translation dependent compositions (two translations)
  print_result("_", compose(r_A_15_to_1, r_A_0_to_2, r_P_0_to_5, r_P_0_to_5, AII).getStr());
  print_result("_", compose(r_A_15_to_1, r_A_0_to_2, r_P_15_to_1, r_P_15_to_1, AII).getStr());
  print_result("_", compose(r_A_15_to_1, r_A_0_to_5, r_P_0_to_5, r_P_15_to_1, AII).getStr());

  print_result("_", compose(r_I_15_to_1, r_I_0_to_2, r_P_0_to_5, r_P_0_to_5, IIA).getStr());
  print_result("_", compose(r_I_15_to_1, r_I_0_to_2, r_P_15_to_1, r_P_15_to_1, IIA).getStr());
  print_result("_", compose(r_I_15_to_1, r_I_1_to_2, r_P_0_to_5, r_P_15_to_1, IIA).getStr());

  print_result("_", compose(r_I_15_to_1, r_A_0_to_2, r_P_0_to_5, r_P_0_to_5, IAI).getStr());
  print_result("_", compose(r_I_15_to_1, r_A_0_to_2, r_P_15_to_1, r_P_15_to_1, IAI).getStr());
  print_result("_", compose(r_I_15_to_1, r_A_0_to_5, r_P_0_to_5, r_P_15_to_1, IAI).getStr());

  print_result("_", compose(r_I_15_to_1, r_I_0_to_2, r_P_0_to_5, r_P_0_to_5, IIR).getStr());
  print_result("_", compose(r_I_15_to_1, r_I_0_to_2, r_P_15_to_1, r_P_15_to_1, IIR).getStr());
  print_result("_", compose(r_I_15_to_1, r_I_1_to_2, r_P_0_to_5, r_P_15_to_1, IIR).getStr());

  print_line_break();
}

void cmd_parser_test(int argc, char* argv[]) {
  cli::Parser parser(argc, argv);
  configure_parser(parser);
  parser.run_and_exit_if_error();
  do_work(parser);
}

int main(int argc, char* argv[]) {

  // print_line_break("Start DAF test!");

  /*
  getRel_test();
  norm_test();
  calOriSeg_test();
  rounding_error_test();
  bRels_test();
  norm_seg_test();
  samepos_test();
  rel_test();
  // union and intersection of relations
  rel_op_test();
  // tests for converse of basic relations
  b_con_test();
  // tests for converse of composite relations
  con_test();
  // tests for composition of basic relations
  b_com_test();
  // tests for composition of composite relations
  com_test();
  */

  // test of command line input parser.
  cmd_parser_test(argc, argv);



  // print_line_break("End DAF test!");
  return 0;
}
