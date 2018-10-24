
#ifndef CONVERSE_H
#define CONVERSE_H

#include <iostream>
using namespace std;

#include "global.h"
#include "b_rel.h"
#include "rel.h"

Rel get_t_con_inv(B_rel);
Rel get_t_con_sci(B_rel);
Rel get_t_con_hmi(B_rel);

Rel converse(B_rel);
Rel converse(B_rel, t_con);
Rel converse(B_rel, B_rel);

Rel converse(Rel);
Rel converse(Rel, t_con);
Rel converse(Rel, Rel);


#endif
