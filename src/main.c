
#include "ringCluster.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Incorrect number of arguments..%i\n", argc);
        exit(1);
    }

    int sizes[] = {3, 4, 5};

    ringCluster *rings = makeRingCluster(sizes, 3);

    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == 0) {
        perror(argv[1]);
        goto end2;
    } 
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    rewind(fp);

    char *data = malloc(len + 1);
    if (fread(data, len, 1, fp) != 1) {
        perror(argv[1]);
        goto end1;
    }
    data[len] = 0; // Ensure null terminated string

    interpret(rings, data, len);

    end1:
    fclose(fp);
    free(data);
    end2:
    freeRingCluster(rings);
}