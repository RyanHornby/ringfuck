

#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

void interpret(ringCluster *rings, char *data, int len) {
    for (int i = 0; i < len; i++) {
        switch(data[i]) {
            case '<':
                spinLeft(rings);
                break;
            case '>':
                spinRight(rings);
                break;
            case '+':
                incRings(rings);
                break;
            case '-':
                decRings(rings);
                break;
            case ',':
                readBytes(rings);
                break;
            case '.':
                printBytes(rings);
                break;
            case '[':
                if (shouldLoop(rings) == 0) {
                    if ((i = findCloseBracket(data, len, i)) == -1) {
                        printf("Unmatched [\n");
                        return;
                    }
                }
                break;
            case ']':
                if ((i = findOpenBracket(data, i)) == -1) {
                    printf("Unmatched ]\n");
                    return;
                }
                break;
            case ' ':
            case '\n':
            case '\t':
                break;
            default:
                printf("Unknown command %c\n", data[i]);
                return;
        }
    }
}

int findCloseBracket(char *data, int len, int i) {
    int count = 0;
    for (int j = i + 1; j < len; j++) {
        if (data[j] == '[') {
            count++;
        } else if (data[j] == ']') {
            if (count == 0) {
                return j;
            }
            count--;
        }
    }
    return -1;
}

int findOpenBracket(char *data, int i) {
    int count = 0;
    for (int j = i - 1; j >= 0; j--) {
        if (data[j] == ']') {
            count++;
        } else if (data[j] == '[') {
            if (count == 0) {
                return j - 1;
            }
            count--;
        }
    }
    return -1;
}

int removeComments(char *data, int len) {
    for (int i = 0; i < len; i++) {
        if (data[i] == '{') {
            char matchedBracket = 0;

            for (int j = i + 1; j < len; j++) {
                if (data[j] == '}') {
                    memmove(data + i, data + j + 1, len - j);
                    len = len - (j - i) - 1;
                    matchedBracket = 1;
                    break;
                }
            }

            // Whole rest of program was commented out
            if (matchedBracket == 0) {
                len = i;
                break;
            }
        }
    }

    return len;
}

int processHeader(char *data, int len, ringCluster **rings) {
    int numRings = 0;
    int newStart = 0;
    int *sizes;
    char *start = data;
    char *end;
    char inNum = 0;

    for (int i = 0; i < len; i++) {
        switch(data[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                inNum = 1;
                break;
            case ' ':
            case '\t':
            case '\n':
                if (inNum) {
                    inNum = 0;
                    numRings++;
                }
                break;
            case '<':
            case '>':
            case ',':
            case '.':
            case '-':
            case '+':
            case '[':
            case ']':
                if (inNum) {
                    numRings++;
                }
                newStart = i;
                i = len;
                break;
        }
    }

    if (numRings == 0) {
        return len;
    }

    sizes = (int *) malloc(numRings * sizeof(int));

    for (int i = 0; i < numRings; i++) {
        errno = 0;
        const long num = strtol(start, &end, 10);

        const char range_error = errno == ERANGE;
 
        if (range_error || num > INT_MAX) {
            printf("Number '%.*s' too large...\n", (int) (end - start), start);
            free(sizes);
            return -1;
        }

        start = end; 
        sizes[i] = num;
    }

    memmove(data, data + newStart, len - newStart + 1);
    len = len - newStart;

    *rings = makeRingCluster(sizes, numRings);

    free(sizes);

    return len;
}