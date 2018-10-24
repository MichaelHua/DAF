#ifndef CMDCONFIG_H
#define CMDCONFIG_H

#include "cmdparser.hpp"
#include "global.h"

using namespace std;

void configure_parser(cli::Parser&);
void do_work(cli::Parser&);

#endif
