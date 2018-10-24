#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

using namespace std;

const string NAME = "DAF";
const string VERSION = "0.1";

namespace config {
  extern float EPSILON;
  extern float ABSO_ANCHOR_ANGLE;
  extern string NO_SAME_POS_REL;
  extern string str_cate[];
}
// phi for anchor
enum rel_cate {EMPTY, SAMPOS, ABSO, INTR, RELA, PHI};

// ternary converse.
enum t_con {INV = 213, SC = 132, SCI = 312, HM = 231, HMI = 321, T_CON_ERROR};

// different types of composition operations
enum com_type {Tau, // direction relation translation
  AAA, III, RRR, // in-category composition
  AAR, ARA, RAA, IRI, RII, // translation-independent across-category
  AIA, AII, AAI, IIA, IAA, IAI, IIR, // translation-dependent across-category
  AIR, ARI, IAR, IRA, RAI, RIA,// translation-dependent across-category
  RRA, ARR, RAR, RRI, IRR, RIR, // non-informative
  P, // anchor relation composition
  P_i, // anchor relation inference
  COM_TYPE_ERROR
};

enum com_sub_type {
  R_31, R_32, // subtypes of RRR
  AI, IA, II, AR, RA, IR, RI, // subtypes of Tau
  COM_SUB_TYPE_ERROR
};

void debug (string, int);
void debug (string, double);
void debug (string);
void debug (string, string);

bool equal(string, string);
void show(string);
void show_inline(string);
void newline(void);

com_type string_to_com_type(string);
com_sub_type string_to_com_sub_type(string);
rel_cate string_to_rel_cate(string);
t_con string_to_t_con(string);

#endif
