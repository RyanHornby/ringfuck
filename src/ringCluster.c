

#include "ringCluster.h"
#include <stdlib.h>

ringCluster* makeRingCluster(int *sizes, int len) {
    ringCluster *rtn = malloc(sizeof(ringCluster));
    rtn->rings = malloc(sizeof(ring*) * len);
    rtn->size = len;
    for (int i = 0; i < len; i++) {
        rtn->rings[i] = makeRing(sizes[i]);
    }

    return rtn;
}

void freeRingCluster(ringCluster *rings) {
    for (int i = 0; i < rings->size; i++) {
        freeRing(rings->rings[i]);
    }
    free(rings->rings);
    free(rings);
}

char shouldLoop(ringCluster *rings) {
    for (int i = 0; i < rings->size; i++) {
        if (rings->rings[i]->data[rings->rings[i]->index] != 0) {
            return 1;
        }
    }

    return 0;
}

void performOperation(ringCluster *rings, void (*operation)(ring *)) {
    for (int i = 0; i < rings->size; i++) {
        (*operation)(rings->rings[i]);
    }
}

void incRings(ringCluster *rings) {
    performOperation(rings, incRing);
}

void decRings(ringCluster *rings) {
    performOperation(rings, decRing);
}

void spinRight(ringCluster *rings) {
    performOperation(rings, moveRight);
}

void spinLeft(ringCluster *rings) {
    performOperation(rings, moveLeft);
}

void printBytes(ringCluster *rings) {
    performOperation(rings, printByte);
}

void readBytes(ringCluster *rings) {
    performOperation(rings, readByte);
}