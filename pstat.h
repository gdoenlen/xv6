#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"
#define TICKET_MIN 1

struct pstat {
  // whether this slot of the process table
  // is in use or not, 1 or 0
  int inuse[NPROC];

  // the number of tickets the process has
  int tickets[NPROC];

  // the pid of each process
  int pid[NPROC];

  // the number of ticks each process
  // has accumulated
  int ticks[NPROC];
};

#endif
