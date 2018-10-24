
#ifndef COMPOSE_H
#define COMPOSE_H

#include <iostream>
using namespace std;

#include "global.h"
#include "b_rel.h"
#include "rel.h"
#include "b_com.h"

Rel compose(Rel, Rel, com_type);
Rel compose(Rel, Rel, com_type, com_sub_type);
Rel compose(Rel, Rel, Rel, com_type);
Rel compose(Rel, Rel, Rel, Rel, com_type);

#endif
