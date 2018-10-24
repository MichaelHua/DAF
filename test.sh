
HELP_TEST=1
BASIC_RELATIONS_TEST=1
QUALIFY_TEST=1
REL_TEST=1
REL_OP_TEST=1
CON_TEST=1
COM_TEST=1
CASE_STUDY=1

if [ "$HELP_TEST" = 1 ]; then
  ./daf -h
  # ./daf --help
fi

if [ "$BASIC_RELATIONS_TEST" = 1 ]; then
  ./daf -m 4 -b
  ./daf -m 2 --basicRelations
  ./daf -m 1 -b
  ./daf -m 0 -b
fi

if [ "$QUALIFY_TEST" = 1 ]; then
  ./daf -m 4 -q -ot A -ops 1 0 0.0 1 1 0.0
  ./daf -m 4 --qualify -ot ABSO -ops 1 1 0.0 1 0 0.0

  ./daf -m 4 -q -ot I -ops 1 0 1.0 1 1 10.0
  ./daf -m 4 -q -ot INTR -ops 1 1 10.0 1 0 1.0

  ./daf -m 4 -q -ot P -ops 1 0 1.0 1 1 10.0
  ./daf -m 4 -q -ot PHI -ops 1 1 10.0 1 0 1.0

  ./daf -m 4 -q -ot R -ops 1 0 0.0 1 1 0.0 0 1 0.0
  ./daf -m 4 -q -ot RELA -ops 1 1 0.0 1 0 0.0 0 1 0.0

  ./daf -m 4 -q -ot S -ops 1 0 0 1 0 0 0 1 0
  ./daf -m 4 -q -ot SAMPOS -ops 1 0 0 1 0 0
  ./daf -m 4 -q -ot S -ops 1 0 0 1 0 0 1 0 0
  ./daf -m 4 -q -ot S -ops 1 0 0 1 1 0 0 1 0
fi

if [ "$REL_TEST" = 1 ]; then
  ./daf -m 4 -u -rs " (ABSO, 0) ( A, 0) (E) "
  ./daf -m 4 -u --relations "(ABSO,0)(A,   0)(A,   0,  1) ( E )"
  ./daf -m 4 -u -rs "(  ABSO, 0) ( A  ,0) (A, 0,1) "
  ./daf -m 4 -u -rs "(ABSO, 0) (A,0) (A,0,1)"

  ./daf -m 4 -u -rs "(I, 0) (INTR, 0) (I, 0, 3)"
  ./daf -m 4 -u -rs "(R, 0) (RELA, 0)"
  ./daf -m 4 -u -rs "(P, 0) (PHI, 0)"
  ./daf -m 4 -u -rs "(ABSO, 0)  (INTR, 0)  (EMPTY) (RELA, 0) (PHI, 0)"

  ./daf -m 4 -u -rs "(R, 17, -1)"
  ./daf -m 4 -u -rs "(P, -1, -3)"
fi

if [ "$REL_OP_TEST" = 1 ]; then
  ./daf -m 4 -u -rs "(ABSO, 0) ( A, 0)"
  ./daf -m 4 --union --relations "(ABSO,0)(A,   0)(A,   0,  1)"
  ./daf -m 4 -u -rs "(A, 0, 1) (A, 1, 2)"
  ./daf -m 4 -u -rs "(A, 0, 1) (A, 36, 1)"

  ./daf -m 4 -i -rs "(PHI, 0) ( P, 0)"
  ./daf -m 4 --intersect -rs "(P,0)(P,   0)(P,   0,  1)"
  ./daf -m 4 -i -rs "(P, 0, 1) (P, 1, 2)"
  ./daf -m 4 -i -rs "(P, 0, 1) (P, 36, 1)"
fi

if [ "$CON_TEST" = 1 ]; then
  ./daf -m 4 -con -rs "(A, 0)"
  ./daf -m 4 --converse -rs "(A, 0, 1)"
  ./daf -m 4 -con -rs "(A, 15, 1)"

  ./daf -m 4 -con -rs "(P, 0, 1)"
  ./daf -m 4 -con -rs "(P, 15, 1)"

  ./daf -m 4 -con -rs "(I, 0, 1) (P, 0, 1)"
  ./daf -m 4 -con -rs "(I, 15, 1) (P, 15, 1)"

  ./daf -m 4 -con -rs "(R, 15, 1)" -ot "INV"
  ./daf -m 4 -con -rs "(R, 15, 1)" -ot "SC"
  ./daf -m 4 -con -rs "(R, 15, 1)" -ot "SCI"
  ./daf -m 4 -con -rs "(R, 15, 1)" -ot "HM"
  ./daf -m 4 -con -rs "(R, 15, 1)" -ot "HMI"
fi

if [ "$COM_TEST" = 1 ]; then
  ./daf -m 4 -com -ot AAA -rs "(A,0,5)(A,5,9)"
  ./daf -m 4 --compose -ot AAA -rs "(A,0,1)(A,15,1)"

  ./daf -m 4 -com -ot Tau -ost AI -rs "(A,15,1)(P,15,1)"
  ./daf -m 4 -com -ot Tau -ost RI -rs "(R,0,2)(P,15,1)"

  ./daf -m 4 -com -ot III -rs "(I,0,1)(I,0,1)(P,15,1)"
  ./daf -m 4 -com -ot III -rs "(I,0,2)(I,1,2)(P,0,2)"

  ./daf -m 4 -com -ot RRR -ost R_31 -rs "(R,0,2)(R,0,1)"
  ./daf -m 4 -com -ot RRR -ost R_32 -rs "(R,0,2)(R,0,1)"

  ./daf -m 4 -com -ot AAR -rs "(A,15,1)(A,0,2)"
  ./daf -m 4 -com -ot ARA -rs "(A,15,1)(R,0,2)"
  ./daf -m 4 -com -ot RAA -rs "(R,0,2)(A,0,2)"
  ./daf -m 4 -com -ot IRI -rs "(I,15,1)(R,0,2)"
  ./daf -m 4 -com -ot RII -rs "(R,0,2)(I,0,2)"

  ./daf -m 4 -com -ot P -rs "(P,0,5)(P,15,1)"
  ./daf -m 4 -com -ot P_i -rs "(P,0,5)(P,15,1)"

  ./daf -m 4 -com -ot AAI -rs "(A,15,1)(A,0,2)(P,0,5)"
  ./daf -m 4 -com -ot IAA -rs "(I,15,1)(A,0,2)(P,0,5)"
  ./daf -m 4 -com -ot AIA -rs "(A,15,1)(I,0,2)(P,0,5)"

  ./daf -m 4 -com -ot AIR -rs "(A,15,1)(I,0,2)(P,0,5)"
  ./daf -m 4 -com -ot ARI -rs "(A,15,1)(R,0,2)(P,0,5)"
  ./daf -m 4 -com -ot IAR -rs "(I,15,1)(A,0,2)(P,0,5)"
  ./daf -m 4 -com -ot IRA -rs "(I,15,1)(R,0,2)(P,0,5)"
  ./daf -m 4 -com -ot RAI -rs "(R,15,1)(A,0,2)(P,0,5)"
  ./daf -m 4 -com -ot RIA -rs "(R,15,1)(I,0,2)(P,0,5)"

  ./daf -m 4 -com -ot AII -rs "(A,15,1)(A,0,2)(P,0,5)(P,0,5)"
  ./daf -m 4 -com -ot IIA -rs "(I,15,1)(I,0,2)(P,0,5)(P,0,5)"
  ./daf -m 4 -com -ot IAI -rs "(I,15,1)(A,0,2)(P,0,5)(P,0,5)"
  ./daf -m 4 -com -ot IIR -rs "(I,15,1)(I,0,2)(P,0,5)(P,0,5)"

  ./daf -m 4 -com -ot RRA -rs "(R,15,1)(R,0,2)"
  ./daf -m 4 -com -ot ARR -rs "(A,15,1)(R,0,2)"
  ./daf -m 4 -com -ot RAR -rs "(R,15,1)(A,0,2)"
  ./daf -m 4 -com -ot RRI -rs "(R,15,1)(R,0,2)"
  ./daf -m 4 -com -ot IRR -rs "(I,15,1)(R,0,2)"
  ./daf -m 4 -com -ot RIR -rs "(R,15,1)(I,0,2)"
fi

if [ "$CASE_STUDY" = 1 ]; then
  ./daf -m 4 -con -rs "(P,4)"
  ./daf -m 4 -com -ot Tau -ost IA  -rs "(I,4)(P,12)"
  ./daf -m 4 -con -rs "(A,14)"
  ./daf -m 4 -com -ot AAR -rs "(A,0)(A,6)"
  ./daf -m 4 -con -ot SCI -rs "(R,6)"
  ./daf -m 4 -com -ot RRR -ost R_31 -rs "(R,12)(R,3,7)"
  ./daf -m 4 -con -rs "(A,8)"
  ./daf -m 4 -com -ot ARA -rs "(A,0)(A,13,3)"
  ./daf -m 4 -com -ot AAA -rs "(A,0)(A,13,3)"
fi
