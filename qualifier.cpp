/*
  Based on qualifier.cpp @ SparQ
*/

#include <iostream>

#include "angle.h"
#include "ori_point.h"
#include "global.h"
#include "b_rel.h"
#include "qualifier.h"
#include "rel_util.h"

using namespace std;

const float EPSILON = config::EPSILON;
const float ABSO_ANCHOR_ANGLE = config::ABSO_ANCHOR_ANGLE;
const string NO_SAME_POS_REL = config::NO_SAME_POS_REL;


// calculate orientation segment
int calOriSeg(int m, float _gap) {
  int result = -1;
  int max = get_MaxSectors(m);

  Angle lb (0.0); // low border
  Angle hb (0.0); // hight border
  Angle gap (_gap);


  for (int iSegNo = 0; iSegNo < max; iSegNo += 2) {
    lb = hb; // set lb to last hb.

    if((iSegNo + 2) == max) {
      hb.set(0.0);
    } else {
      hb.set(((float) ((iSegNo + 2) * 2.0 * M_PI)) / (float) max );
    }

    if(abs(lb.diff(gap)) < EPSILON) {
      return iSegNo;
    }

    if(abs(hb.diff(gap)) < EPSILON) {
      return iSegNo + 2;
    }

    float gap_to_lb = gap.get() - lb.get();
    float hb_to_gap = hb.get() - gap.get();
    if (hb.get() == 0.0) {
      hb_to_gap = 2 * M_PI - gap.get();
    }

    if(gap_to_lb >= EPSILON && hb_to_gap >= EPSILON) {
      return iSegNo + 1;
    }
  }

  return result;
}

// get direction relations
B_rel getDirRel(int m, double anchor, OriPoint opA, OriPoint opB, rel_cate cate) {
  OriPoint opOrigin(0, 0, 0);
  OriPoint opB_1(opB);

  opB_1.shift(opOrigin-opA);
  opB_1.rotate(-anchor);

  int iSegNo = calOriSeg(m, opOrigin.GetAngleTo(opB_1));
  return B_rel(cate, iSegNo);
}

B_rel getRel(int m, rel_cate cate, OriPoint opA, OriPoint opB) {
  if (cate == SAMPOS) {
    return getSamePosRel(m, opA, opB);
  }

  if (cate == ABSO) {
    return getDirRel(m, ABSO_ANCHOR_ANGLE, opA, opB, ABSO);
  }

  if (cate == INTR) {
    return getDirRel(m, opA.getAnchorAngle(), opA, opB, INTR);
  }

  if (cate == PHI) {
    float gap = opB.getANCHOR() - opA.getANCHOR();
    return B_rel(PHI, calOriSeg(m, gap));
  }

  return B_rel(); // return an empty relation if sth goes wrong
}

B_rel getRel(int m, rel_cate cate, OriPoint opA, OriPoint opB, OriPoint opC) {
  if (cate == SAMPOS) {
    return getSamePosRel(m, opA, opB, opC);
  }

  if (cate == RELA) {
    return getDirRel(m, opA.GetAngleTo(opB), opB, opC, RELA);
  }

  return B_rel();
}

// get same position relations
B_rel getSamePosRel(int m, OriPoint opA, OriPoint opB) {
  if(opA.samePos(opB)) {
    return B_rel(SAMPOS, 2);
  }

  return B_rel();
}

B_rel getSamePosRel(int m, OriPoint opA, OriPoint opB, OriPoint opC) {
  if (opA.samePos(opB) && opA.samePos(opC)) {
    return B_rel(SAMPOS, 3);
  }

  if (opA.samePos(opB)) {
    return B_rel(SAMPOS, 12);
  }

  if (opB.samePos(opC)) {
    return B_rel(SAMPOS, 23);
  }

  if (opA.samePos(opC)) {
    return B_rel(SAMPOS, 13);
  }

  return B_rel();
}
