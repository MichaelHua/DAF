#include "ori_point.h"
#include "b_rel.h"

using namespace std;


// get same position relations
B_rel getSamePosRel(int m, OriPoint opA, OriPoint opB);
B_rel getSamePosRel(int m, OriPoint opA, OriPoint opB, OriPoint opC);

// get absolute relations
B_rel getRel(int m, rel_cate cate, OriPoint opA, OriPoint opB);
B_rel getRel(int m, rel_cate cate, OriPoint opA, OriPoint opB, OriPoint opC);

int calOriSeg(int, float);
