/*
    ring.c provides helper functions for using the ring struct (from ring.h)
    as a circular buffer. 
*/
#include "ring.h"
#include <stdlib.h>
#include <stdio.h>

ring* makeRing(int size) {
    ring *rtn = malloc(sizeof(ring));
    rtn->data = calloc(1, size);
    rtn->size = size;
    rtn->index = 0;

    return rtn;
}

void freeRing(ring *ring) {
    free(ring->data);
    free(ring);
}

void moveRight(ring *ring) {
    if (ring->index + 1 == ring->size) {
        ring->index = 0;
    } else {
        ring->index++;
    }
}

void moveLeft(ring *ring) {
    if (ring->index == 0) {
        ring->index = ring->size - 1;
    } else {
        ring->index--;
    }
}

void incRing(ring *ring) {
    ring->data[ring->index]++;
}

void decRing(ring *ring) {
    ring->data[ring->index]--;
}

void printByte(ring *ring) {
    printf("%c", ring->data[ring->index]);
}

void readByte(ring *ring) {
    char buf[2];
    fgets(buf, 2, stdin);
    ring->data[ring->index] = buf[0];
}