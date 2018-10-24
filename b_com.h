
#ifndef B_COMPOSE_H
#define B_COMPOSE_H

#include <iostream>
using namespace std;

#include "global.h"
#include "b_rel.h"
#include "rel.h"

Rel b_com(B_rel, B_rel, com_type);
Rel b_com(B_rel, B_rel, com_type, com_sub_type);
Rel b_com(B_rel, B_rel, B_rel, com_type);
Rel b_com(B_rel, B_rel, B_rel, B_rel, com_type);

Rel b_com_aaa(B_rel, B_rel);
Rel b_com_aar(B_rel, B_rel);
Rel b_com_ara(B_rel, B_rel);
Rel b_com_raa(B_rel, B_rel);
Rel b_com_iri(B_rel, B_rel);
Rel b_com_rii(B_rel, B_rel);

Rel b_com_phi(B_rel, B_rel);
Rel b_com_phi_infer(B_rel, B_rel);

Rel b_com_tau(B_rel, B_rel, com_sub_type);
Rel b_com_rrr(B_rel, B_rel, com_sub_type);

Rel b_com_iii(B_rel, B_rel, B_rel);
Rel b_com_aai(B_rel, B_rel, B_rel);
Rel b_com_iaa(B_rel, B_rel, B_rel);
Rel b_com_aia(B_rel, B_rel, B_rel);

Rel b_com_air(B_rel, B_rel, B_rel);
Rel b_com_ari(B_rel, B_rel, B_rel);
Rel b_com_iar(B_rel, B_rel, B_rel);
Rel b_com_ira(B_rel, B_rel, B_rel);
Rel b_com_rai(B_rel, B_rel, B_rel);
Rel b_com_ria(B_rel, B_rel, B_rel);

Rel b_com_aii(B_rel, B_rel, B_rel, B_rel);
Rel b_com_iia(B_rel, B_rel, B_rel, B_rel);
Rel b_com_iai(B_rel, B_rel, B_rel, B_rel);
Rel b_com_iir(B_rel, B_rel, B_rel, B_rel);


#endif
