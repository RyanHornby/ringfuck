

#include "interpreter.h"
#include <stdio.h>

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