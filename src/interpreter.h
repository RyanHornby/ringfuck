
#include "ringCluster.h"

#ifndef INTERPRETER_H
#define INTERPRETER_H

void interpret(ringCluster *, char *, int);
int findCloseBracket(char *, int, int);
int findOpenBracket(char *, int);
int removeComments(char *, int);
int processHeader(char *, int, ringCluster **);

#endif