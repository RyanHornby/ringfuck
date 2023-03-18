
#include "ringCluster.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    ringCluster *rings;
    int rtn = 0;
    FILE *fp;
    
    if (argc != 2) {
        printf("Incorrect number of arguments..%i\n", argc);
        rtn = 1;
        goto end2;
    }
    
    if ((fp = fopen(argv[1], "r")) == 0) {
        perror(argv[1]);
        rtn = 1;
        goto end2;
    } 
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    rewind(fp);

    char *data = malloc(len);
    if (fread(data, len, 1, fp) != 1) {
        perror(argv[1]);
        rtn = 2;
        goto end1;
    }

    int newLen = removeComments(data, len);
    newLen = processHeader(data, newLen, &rings);
    interpret(rings, data, newLen);

    freeRingCluster(rings);

    end1:
    fclose(fp);
    free(data);
    end2:
    return rtn;    
}