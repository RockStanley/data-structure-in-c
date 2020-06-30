// [2020-06-30 10:56:43] 
// [2020-06-30 15:50:26]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFile(char *filename);
char* readLine(FILE *file);
char* isInclude(char* line);
char* filename(char *line, int start, int end);

int main(int argc, char *argv[]) {
    char *filename;

    if (argc > 1) {
        filename = argv[1];
        printFile(filename);
    }
    return 0;
}

void printFile(char *filename) {
    FILE *file = fopen(filename, "r");
    char *line;
    char *includeFile;
    
    if (file != NULL) {
        while ((line = readLine(file)) != NULL) {
            if ((includeFile = isInclude(line)) != NULL) {
                printFile(includeFile);
            } else {
                printf("%s", line);
            }
        }
    }
}

// reads a whole line, returns NULL when reaching file end.
char* readLine(FILE *file) {
    int i = 0, size = 80;
    int c;
    char *buf = malloc(size * sizeof(char));
    
    while ((c = fgetc(file)) != EOF) {
        buf[i++] = c;
        if (i == size) {
            size = size + 80;
            buf = realloc(buf, size * sizeof(char));
        }
        if (c == '\n') {
            buf[i] = '\0';
            return buf;
        }
    }
    if (i > 0) {
        buf[i] = '\0';
        return buf;
    } else {
        return NULL;
    }
}

// decides if this is a include line
char* isInclude(char *line) {
    const char *include = "#include ";
    int cmplen = 9;
    int linelen;
    int i, ifnamestart, ifnameend;
    char *fname;

    if (strncmp(line, include, cmplen) == 0) {
        linelen = strlen(line);
        // remove trailing whitespaces
        for (i = 0; i < linelen; i++) {
            if (line[i] == '"') {
                ifnamestart = i + 1;
                for (i = i + 1; i < linelen; i++) {
                    if (line[i] == '"') {
                        ifnameend = i;
                        return filename(line, ifnamestart, ifnameend);
                    }
                }
                break;
            } else if (line[i] == '<') {
                for (i = i + 1; i < linelen; i++) {
                    if (line[i] == '>') {
                        ifnameend = i;
                        return filename(line, ifnamestart, ifnameend);
                    }
                }
                break;
            }
        }
    }
    return NULL;
}

char* filename(char *line, int start, int end) {
    char *fname = malloc((end - start + 1) * sizeof(char));
    return strncpy(fname, &line[start], end - start);
}