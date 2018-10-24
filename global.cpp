#include <math.h>
#include <iostream>
#include "global.h"

using namespace std;


namespace config {
  float EPSILON = 0.000001; // precise within 1e-5, but no guarantee with 1e-6
  float ABSO_ANCHOR_ANGLE = M_PI / 2;
  string NO_SAME_POS_REL = "NO_SAME_POS_REL";
  string str_cate[] = {"E", "S", "A", "I", "R", "P"};
}

void debug (string varName, int i) {
  cout << "**[DEBUG]** " << varName << " --> " << to_string(i) << endl;
}

void debug (string varName, double f) {
  cout << "**[DEBUG]** " << varName << " --> " << f << endl;
}

void debug (string varName, string str) {
  cout << "**[DEBUG]** " << varName << " --> " << str << endl;
}

void debug (string mark) {
  cout << "**[DEBUG]*[MARK]** " << mark << endl;
}

bool equal(string str1, string str2) {
  return str1.compare(str2) == 0;
}

void show(string result) {
  cout << result << endl;
}

void show_inline(string result) {
  cout << result << " ";
}

void newline(void) {
  cout << endl;
}

com_type string_to_com_type(string str) {
  if (equal(str, "Tau")) return Tau;
  if (equal(str, "AAA")) return AAA;
  if (equal(str, "III")) return III;
  if (equal(str, "RRR")) return RRR;
  if (equal(str, "AAR")) return AAR;
  if (equal(str, "ARA")) return ARA;
  if (equal(str, "RAA")) return RAA;
  if (equal(str, "IRI")) return IRI;
  if (equal(str, "RII")) return RII;
  if (equal(str, "AIA")) return AIA;
  if (equal(str, "AII")) return AII;
  if (equal(str, "AAI")) return AAI;
  if (equal(str, "IIA")) return IIA;
  if (equal(str, "IAA")) return IAA;
  if (equal(str, "IAI")) return IAI;
  if (equal(str, "IIR")) return IIR;
  if (equal(str, "RRA")) return RRA;
  if (equal(str, "ARR")) return ARR;
  if (equal(str, "RAR")) return RAR;
  if (equal(str, "RRI")) return RRI;
  if (equal(str, "IRR")) return IRR;
  if (equal(str, "RIR")) return RIR;
  if (equal(str, "P")) return P;
  if (equal(str, "P_i")) return P_i;

  if (equal(str, "AIR")) return AIR;
  if (equal(str, "ARI")) return ARI;
  if (equal(str, "IAR")) return IAR;
  if (equal(str, "IRA")) return IRA;
  if (equal(str, "RAI")) return RAI;
  if (equal(str, "RIA")) return RIA;

  return COM_TYPE_ERROR;
}

com_sub_type string_to_com_sub_type(string str) {
  if (equal(str, "R_31")) return R_31;
  if (equal(str, "R_32")) return R_32;
  if (equal(str, "AI")) return AI;
  if (equal(str, "IA")) return IA;
  if (equal(str, "II")) return II;
  if (equal(str, "AR")) return AR;
  if (equal(str, "RA")) return RA;
  if (equal(str, "IR")) return IR;
  if (equal(str, "RI")) return RI;

  return COM_SUB_TYPE_ERROR;
}

t_con string_to_t_con(string str) {
  if (equal(str, "INV")) return INV;
  if (equal(str, "SC")) return SC;
  if (equal(str, "SCI")) return SCI;
  if (equal(str, "HM")) return HM;
  if (equal(str, "HMI")) return HMI;

  return T_CON_ERROR;
}

rel_cate string_to_rel_cate(string str) {
  if (str.find("ABSO") != string::npos) return ABSO;
  if (str.find("INTR") != string::npos) return INTR;
  if (str.find("RELA") != string::npos) return RELA;
  if (str.find("PHI") != string::npos) return PHI;
  if (str.find("SAMPOS") != string::npos) return SAMPOS;
  if (str.find("A") != string::npos) return ABSO;
  if (str.find("I") != string::npos) return INTR;
  if (str.find("R") != string::npos) return RELA;
  if (str.find("P") != string::npos) return PHI;
  if (str.find("S") != string::npos) return SAMPOS;

  return EMPTY;
}
