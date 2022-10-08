
#include "ringCluster.h"

int main(char **argv, int argc) {
    int sizes[] = {3, 4, 5};

    ringCluster *rings = makeRingCluster(sizes, 3);

    for (int i = 0; i < 72; i++) {
        incRings(rings);
    }

    printBytes(rings);
}