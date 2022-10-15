

#include "ring.h"

#ifndef RING_CLUSTER_H
#define RING_CLUSTER_H

typedef struct {
    ring **rings;
    int size;
} ringCluster;

ringCluster* makeRingCluster(int *, int);
void freeRingCluster(ringCluster *);
void incRings(ringCluster *);
void decRings(ringCluster *);
void spinRight(ringCluster *);
void spinLeft(ringCluster *);
void printBytes(ringCluster *);
void readBytes(ringCluster *);
char shouldLoop(ringCluster *);

#endif