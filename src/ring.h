

#ifndef RING_H
#define RING_H

typedef struct {
    char *data;
    int size;
    int index;
} ring;

ring* makeRing(int size);
void freeRing(ring *ring);
void moveRight(ring *);
void moveLeft(ring *);
void incRing(ring *);
void decRing(ring *);
void printByte(ring *);
void readByte(ring *);

#endif