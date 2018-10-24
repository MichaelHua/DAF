#ifndef RELS_FOR_TEST_H
#define RELS_FOR_TEST_H

#include "b_rel.h"
#include "rel.h"


B_rel r_e; // empty
B_rel S_2(SAMPOS, 2);
B_rel S_12(SAMPOS, 12);
B_rel S_13(SAMPOS, 13);
B_rel S_23(SAMPOS, 23);
B_rel S_3(SAMPOS, 3);

// for tests, default granularity is 4.
B_rel A_n_1(ABSO, -1, 4);
B_rel A_0(ABSO, 0, 4);
B_rel A_1(ABSO, 1, 4);
B_rel A_2(ABSO, 2, 4);
B_rel A_3(ABSO, 3, 4);
B_rel A_4(ABSO, 4, 4);
B_rel A_5(ABSO, 5, 4);
B_rel A_6(ABSO, 6, 4);
B_rel A_7(ABSO, 7, 4);
B_rel A_8(ABSO, 8, 4);
B_rel A_9(ABSO, 9, 4);
B_rel A_10(ABSO, 10, 4);
B_rel A_11(ABSO, 11, 4);
B_rel A_12(ABSO, 12, 4);
B_rel A_13(ABSO, 13, 4);
B_rel A_14(ABSO, 14, 4);
B_rel A_15(ABSO, 15, 4);
B_rel A_16(ABSO, 16, 4);
B_rel A_17(ABSO, 17, 4);
B_rel A_30(ABSO, 30, 4);

B_rel I_n_1(INTR, -1, 4);
B_rel I_0(INTR, 0, 4);
B_rel I_1(INTR, 1, 4);
B_rel I_2(INTR, 2, 4);
B_rel I_3(INTR, 3, 4);
B_rel I_4(INTR, 4, 4);
B_rel I_5(INTR, 5, 4);
B_rel I_6(INTR, 6, 4);
B_rel I_7(INTR, 7, 4);
B_rel I_8(INTR, 8, 4);
B_rel I_9(INTR, 9, 4);
B_rel I_10(INTR, 10, 4);
B_rel I_11(INTR, 11, 4);
B_rel I_12(INTR, 12, 4);
B_rel I_13(INTR, 13, 4);
B_rel I_14(INTR, 14, 4);
B_rel I_15(INTR, 15, 4);
B_rel I_16(INTR, 16, 4);
B_rel I_17(INTR, 17, 4);
B_rel I_30(INTR, 30, 4);

B_rel R_n_1(RELA, -1, 4);
B_rel R_0(RELA, 0, 4);
B_rel R_1(RELA, 1, 4);
B_rel R_2(RELA, 2, 4);
B_rel R_3(RELA, 3, 4);
B_rel R_4(RELA, 4, 4);
B_rel R_5(RELA, 5, 4);
B_rel R_6(RELA, 6, 4);
B_rel R_7(RELA, 7, 4);
B_rel R_8(RELA, 8, 4);
B_rel R_9(RELA, 9, 4);
B_rel R_10(RELA, 10, 4);
B_rel R_11(RELA, 11, 4);
B_rel R_12(RELA, 12, 4);
B_rel R_13(RELA, 13, 4);
B_rel R_14(RELA, 14, 4);
B_rel R_15(RELA, 15, 4);
B_rel R_16(RELA, 16, 4);
B_rel R_17(RELA, 17, 4);
B_rel R_30(RELA, 30, 4);

B_rel P_n_1(PHI, -1, 4);
B_rel P_0(PHI, 0, 4);
B_rel P_1(PHI, 1, 4);
B_rel P_2(PHI, 2, 4);
B_rel P_3(PHI, 3, 4);
B_rel P_4(PHI, 4, 4);
B_rel P_5(PHI, 5, 4);
B_rel P_6(PHI, 6, 4);
B_rel P_7(PHI, 7, 4);
B_rel P_8(PHI, 8, 4);
B_rel P_9(PHI, 9, 4);
B_rel P_10(PHI, 10, 4);
B_rel P_11(PHI, 11, 4);
B_rel P_12(PHI, 12, 4);
B_rel P_13(PHI, 13, 4);
B_rel P_14(PHI, 14, 4);
B_rel P_15(PHI, 15, 4);
B_rel P_16(PHI, 16, 4);
B_rel P_17(PHI, 17, 4);
B_rel P_30(PHI, 30 ,4);

Rel r_E(r_e);
Rel r_A_0(A_0);
Rel r_A_1(A_1);
Rel r_A_0_to_1 = get_rel_from_bRels(0, 1, ABSO, 4);
Rel r_A_1_to_2 = get_rel_from_bRels(1, 2, ABSO, 4);
Rel r_A_0_to_2 = get_rel_from_bRels(0, 2, ABSO, 4);
Rel r_A_0_to_5 = get_rel_from_bRels(0, 5, ABSO, 4);
Rel r_A_5_to_9 = get_rel_from_bRels(5, 9, ABSO, 4);
Rel r_A_15_to_1 = get_rel_from_bRels(15, 1, ABSO, 4);
Rel r_A_0_5(ABSO, 4, {0, 5});


Rel r_I_0(I_0);
Rel r_I_1(I_1);
Rel r_I_0_to_1 = get_rel_from_bRels(0, 1, INTR, 4);
Rel r_I_1_to_2 = get_rel_from_bRels(1, 2, INTR, 4);
Rel r_I_0_to_2 = get_rel_from_bRels(0, 2, INTR, 4);
Rel r_I_0_to_5 = get_rel_from_bRels(0, 5, INTR, 4);
Rel r_I_5_to_9 = get_rel_from_bRels(5, 9, INTR, 4);
Rel r_I_15_to_1 = get_rel_from_bRels(15, 1, INTR, 4);
Rel r_I_0_5(INTR, 4, {0, 5});

Rel r_R_0(R_0);
Rel r_R_1(R_1);
Rel r_R_0_to_1 = get_rel_from_bRels(0, 1, RELA, 4);
Rel r_R_1_to_2 = get_rel_from_bRels(1, 2, RELA, 4);
Rel r_R_0_to_2 = get_rel_from_bRels(0, 2, RELA, 4);
Rel r_R_0_to_5 = get_rel_from_bRels(0, 5, RELA, 4);
Rel r_R_5_to_9 = get_rel_from_bRels(5, 9, RELA, 4);
Rel r_R_15_to_1 = get_rel_from_bRels(15, 1, RELA, 4);
Rel r_R_0_5(RELA, 4, {0, 5});

Rel r_P_0(P_0);
Rel r_P_1(P_1);
Rel r_P_0_to_1 = get_rel_from_bRels(0, 1, PHI, 4);
Rel r_P_1_to_2 = get_rel_from_bRels(1, 2, PHI, 4);
Rel r_P_0_to_2 = get_rel_from_bRels(0, 2, PHI, 4);
Rel r_P_0_to_5 = get_rel_from_bRels(0, 5, PHI, 4);
Rel r_P_5_to_9 = get_rel_from_bRels(5, 9, PHI, 4);
Rel r_P_15_to_1 = get_rel_from_bRels(15, 1, PHI, 4);
Rel r_P_0_5(PHI, 4, {0, 5});

#endif
