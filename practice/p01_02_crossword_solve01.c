// [2020-06-29 01:37:49] 
// [2020-06-29 03:24:16]
#include <stdio.h>
#include <stdlib.h>

typedef struct cnode {
    struct cnode *c[26];
    short terminated;
} CNode;

CNode* createWordTree(char **words, int size);
CNode* insertChar(CNode *p, char c);
void scan(char *m, int w, int h, CNode *tree);

int main(void) {
    char *words[] = {"this", "two", "fat", "that"};
    char matrix[4][4] = {{'t', 'h', 'i', 's'},
        {'w', 'a', 't', 's'},
        {'o', 'a', 'h', 'g'},
        {'f', 'g', 'd', 't'}};
    CNode *tree = createWordTree(words, 4);
    
    scan(&matrix[0][0], 4, 4, tree);
    return 0;
}

// create word tree
// assume all word letters are in lower case
CNode* createWordTree(char **words, int size) {
    CNode *tree = calloc(1, sizeof(CNode));
    CNode *p = tree;
    int i, j;

    for (i = 0; i < size; i++) {
        p = tree;
        for (j = 0; words[i][j] != '\0'; j++) {
            p = insertChar(p, words[i][j]);
        }
        p->terminated = 1;
    }
    return tree;
}

// insert a character c as a child of character p.
// c may have either been in the tree or not been in the tree.
// returns the pointer to the inserted character c.
CNode* insertChar(CNode *p, char c) {
    CNode *child = p->c[c - 'a'];

    if (child == NULL) {
        child = calloc(1, sizeof(CNode));
        p->c[c - 'a'] = child;
    }
    return child;
}

// scan the matrix m , print all words found.
// w is the matrix's width
// h is the matrix's height
void scan(char *m, int w, int h, CNode *tree) {
    int x, y, si, l; // l: str len
    int nx, ny;
    int steps[8][2] = {{0, 1}, {0, -1}, {1, 1}, {1, 0}, {1, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++) {
            for (si = 0; si < 8; si++) {
                l = 1;
                CNode *p = tree;
                for (;; l++) {
                    nx = x + steps[si][0] * (l - 1);
                    ny = y + steps[si][1] * (l - 1);
                    if (nx < 0 || nx >= w || ny < 0 || ny >= w) {
                        break;
                    }
                    // TODO: comment
                    p = p->c[m[nx * w + ny] - 'a'];
                    if (p == NULL) {
                        break;
                    }
                    if (p->terminated) {
                        printf("find result: (%d, %d) (%d, %d) %d\n", x + 1, y + 1, steps[si][0], steps[si][1], l); // coordination starts from 1.
                    }
                }
            }
        }
    }
}
