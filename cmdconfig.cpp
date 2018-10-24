#include <iostream>
#include <math.h>
#include <set>
#include <algorithm>


#include "cmdparser.hpp"
#include "global.h"
#include "cmdconfig.h"
#include "daf.h"
#include "ori_point.h"
#include "qualifier.h"
#include "rel.h"
#include "rel_util.h"
#include "converse.h"
#include "compose.h"

using namespace std;

void cmd_show (string keyword, string content, int m) {
  show("[" + NAME + "_" + to_string(m) + "][" + keyword + "] " + content);
}

void cmd_format_error (string keyword, int m) {
  show("[" + NAME + "_" + to_string(m) + "][" + keyword + "] " +
    "wrong format. For more help use --help or -h.");
}

void do_qualify(cli::Parser& parser, int m) {
  string kw = "qualify";
  string ot = parser.get<string>("ot"); // operation type
  vector<float> ops = parser.get<vector<float>>("ops");
  rel_cate rc = string_to_rel_cate(ot);

  int size = (int) ops.size();
  if (size == 6) { // two ops
    OriPoint opA(ops.at(0), ops.at(1), ops.at(2));
    OriPoint opB(ops.at(3), ops.at(4), ops.at(5));
    cmd_show(kw, getRel(m, rc, opA, opB).getStr(), m);
  }

  if (size == 9) { // three ops
    OriPoint opA(ops.at(0), ops.at(1), ops.at(2));
    OriPoint opB(ops.at(3), ops.at(4), ops.at(5));
    OriPoint opC(ops.at(6), ops.at(7), ops.at(8));
    cmd_show(kw, getRel(m, rc, opA, opB, opC).getStr(), m);
  }
}

vector<string> split(string str, string delimiter){
    vector<string> result;
    while (str.size()) {
        int index = str.find(delimiter);
        if (index != (int) string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + delimiter.size());
            if (str.size() == 0) {
              result.push_back(str);
            }
        } else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

vector<Rel> get_rels(cli::Parser& parser, int m) {
  string rs = parser.get<string>("rs"); // relations
  vector<string> rels_str = split(rs, ")");

  vector<Rel> rels;

  for (auto it = rels_str.begin(); it != rels_str.end(); it++) {
    vector<string> rel_str = split(*it, ",");

    if ((int) rel_str.size() == 1) {
      string type = rel_str.at(0);

      if (type.find("E") != string::npos) {
        rels.push_back(Rel());
      }
    }

    if ((int) rel_str.size() == 2) {
      string type = rel_str.at(0);
      int seg = stoi(rel_str.at(1));
      seg = norm_seg(m, seg);
      Rel rel = Rel(B_rel(string_to_rel_cate(type), seg, m));

      rels.push_back(rel);
    }

    if ((int) rel_str.size() == 3) {
      string type = rel_str.at(0);
      int startSeg = stoi(rel_str.at(1));
      int endSeg = stoi(rel_str.at(2));
      Rel rel = get_rel_from_bRels(startSeg, endSeg,
        string_to_rel_cate(type), m);

      rels.push_back(rel);
    }
  }

  // show rels
  string kw = "relations";
  string content = "";
  for (auto it = rels.begin(); it != rels.end(); it++) {
    content += (*it).getStr() + " ";
  }
  cmd_show(kw, content, m);

  return rels;
}

void do_union(cli::Parser& parser, int m) {
  vector<Rel> rels = get_rels(parser, m);
  string kw = "union";

  if ((int) rels.size() != 2) {
    cmd_format_error(kw, m);
  } else {

    string content = cup(rels.at(0), rels.at(1)).getStr();
    cmd_show(kw, content, m);
  }
}

void do_intersect(cli::Parser& parser, int m) {
  vector<Rel> rels = get_rels(parser, m);
  string kw = "intersect";

  if ((int) rels.size() != 2) {
    cmd_format_error(kw, m);
  } else {

    string content = cap(rels.at(0), rels.at(1)).getStr();
    cmd_show(kw, content, m);
  }
}

void do_converse(cli::Parser& parser, int m) {
  vector<Rel> rels = get_rels(parser, m);
  string kw = "converse";

  if ((int) rels.size() == 1) {
    Rel rel = rels.at(0);
    string content = "";

    if (rel.getCate() == ABSO || rel.getCate() == PHI) {
      content = converse(rel).getStr();
      cmd_show(kw, content, m);
    }

    if (rel.getCate() == RELA) {
      string ot = parser.get<string>("ot");
      t_con tc = string_to_t_con(ot);
      content = converse(rel, tc).getStr();

      cmd_show(kw  + " " + ot, content, m);
    }

  } else if ((int) rels.size() == 2) {
    Rel rel = rels.at(0);
    Rel anchor = rels.at(1);
    string content = converse(rel, anchor).getStr();
    cmd_show(kw, content, m);

  } else {
    cmd_format_error(kw, m);
  }
}

void do_compose(cli::Parser& parser, int m) {
  vector<Rel> rels = get_rels(parser, m);
  string kw = "compose";
  string ot = parser.get<string>("ot");
  com_type ct = string_to_com_type(ot);
  string content = "";
  bool error = true;

  if (equal(ot, "AAA") || equal(ot, "AAR") || equal(ot, "ARA")
    || equal(ot, "RAA") || equal(ot, "IRI") || equal(ot, "RII")
    || equal(ot, "P") || equal(ot, "P_i") || equal(ot, "RRA")
    || equal(ot, "ARR") || equal(ot, "RAR") || equal(ot, "RRI")
    || equal(ot, "IRR") || equal(ot, "RIR")) {

    if ((int) rels.size() == 2) {
      Rel r1 = rels.at(0);
      Rel r2 = rels.at(1);
      content = compose(r1, r2, ct).getStr();
      cmd_show(kw + " " + ot, content, m);
      error = false;
    }
  }

  if (equal(ot, "Tau") || equal(ot, "RRR")) {
    if ((int) rels.size() == 2) {
      string ost = parser.get<string>("ost");
      com_sub_type cst = string_to_com_sub_type(ost);
      Rel r1 = rels.at(0);
      Rel r2 = rels.at(1);

      content = compose(r1, r2, ct, cst).getStr();
      cmd_show(kw + " " + ot + " " + ost, content, m);
      error = false;
    }
  }

  if (equal(ot, "III") || equal(ot, "AIA") || equal(ot, "AAI")
    || equal(ot, "AAI") || equal(ot, "IAA")) {

    if ((int) rels.size() == 3) {
      Rel r1 = rels.at(0);
      Rel r2 = rels.at(1);
      Rel r3 = rels.at(2);

      content = compose(r1, r2, r3, ct).getStr();
      cmd_show(kw + " " + ot, content, m);
      error = false;
    }
  }

  if (equal(ot, "AII") || equal(ot, "IIA") || equal(ot, "IAI")
    || equal(ot, "IIR")) {

    if ((int) rels.size() == 4) {
      Rel r1 = rels.at(0);
      Rel r2 = rels.at(1);
      Rel r3 = rels.at(2);
      Rel r4 = rels.at(3);

      content = compose(r1, r2, r3, r4, ct).getStr();
      cmd_show(kw + " " + ot, content, m);
      error = false;
    }
  }

  if (error) {
    cmd_format_error(kw, m);
  }
}

void configure_parser(cli::Parser& parser) {
  parser.set_optional<bool>("v", "version", false, "Current version.\n");
  parser.set_optional<int>("m", "granularity", 4, "Granularity of DAF.\n");
  parser.set_optional<bool>("b", "basicRelations", false, "Print" \
    " basic relations.\n");

  parser.set_optional<bool>("q", "qualify", false, "Get qualitative" \
    " spatial relations from quantitative input. Use -ot for \n"
    "   different types of relations. Types available:" \
    " S (or SAMPOS), A (or ABSO),\n"\
    "   I (or INTR), R (or RELA), P (or PHI).\n");

  parser.set_optional<vector<float>>("ops", "orientedPoints", \
    { }, "Input oriented points. Please follow the" \
    "format: x_op1 y_op1 phi_op1 x_op2 \n" \
    "   y_op2 phi_op2 ...\n");

  parser.set_optional<string>("rs", "relations", "(ABSO, 0) (E) (A, 0, 1)",
    "Input relations. Format: \"(type, seg)\" or \"(type, startSeg, endSeg).\""\
    "\n   \"(E)\" or \"(EMPTY)\" for an empty relation.\n");

  parser.set_optional<bool>("u", "union", false, "Get the union of" \
    "two relations. Arity: 2\n");

  parser.set_optional<bool>("i", "intersect", false, "Get the" \
    " intersect of two relations. Arity: 2\n");

  parser.set_optional<bool>("con", "converse", false, "Get the" \
    " converse of a relation. Arity varies on different types: 2 for\n"\
    "   intrinsic relations and 1 for the rest." \
    " Use -ot for different converse\n   operations on relative relations." \
    " Types available: INV, SC, SCI, HM, HMI.\n");

  parser.set_optional<bool>("com", "compose", false, "Get the" \
    " composition of two relations. Types available are as follows.\n"
    "   1. In-category (arity in brackets): AAA(2), III(3), RRR(2,"\
    " subtypes: R_31,\n      R_32);"\
    "\n   2. Translation-independent across-category:"\
    " AAR(2), ARA(2), RAA(2), IRI(2),\n      RII(2); "\
    "\n   3. Translation-dependent across-category: AIA (3), AII (4), "\
    "AAI (3),\n      IIA(4), IAA(3), IAI(4), IIR(4);"\
    "\n   4. Non-informative across category: RRA, ARR, RAR, RRI, IRR,"\
    " RIR;\n   5. Direction relation translation: Tau(2, subtypes: AI, IA, II,"\
    " AR, RA, IR,\n      RI); \n   6. Anchor relation composition: P(2);"\
    " \n   7. Anchor relation inference: P_i(2).\n");

  parser.set_optional<string>("ot", "operationType", "NULL", "Input" \
    " the type of an operation.");
  parser.set_optional<string>("ost", "operationSubType", "NULL", "Input" \
    " the sub-type of an operation.");
}

void do_work(cli::Parser& parser) {
  int m = 4;
  bool version = parser.get<bool>("v");
  if (version) {
    cmd_show("version", VERSION, m);
  }

  m = parser.get<int>("m");
  Daf daf(m);

  bool printBRels = parser.get<bool>("b");
  if (printBRels) {
    cmd_show("basic relations", daf.getBRelsStr() ,m);
  }

  bool qualify = parser.get<bool>("q");
  if (qualify) {
    do_qualify(parser, m);
  }

  bool union_op = parser.get<bool>("u");
  if (union_op) {
    do_union(parser, m);
  }

  bool intersect_op = parser.get<bool>("i");
  if (intersect_op) {
    do_intersect(parser, m);
  }

  bool converse = parser.get<bool>("con");
  if (converse) {
    do_converse(parser, m);
  }

  bool compose = parser.get<bool>("com");
  if (compose) {
    do_compose(parser, m);
  }
}
