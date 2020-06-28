// [2020-06-26 23:03:06]
// [2020-06-27 00:11:38]
/* run result:
        10 -   0.000009s
        30 -   0.000003s
       100 -   0.000015s
      1000 -   0.001367s
     10000 -   0.115207s
    100000 -  10.434824s
    300000 -  95.178481s
   1000000 - 1135.633033s
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000000
#define LENGTH 30
#define K ( LENGTH / 2 )

void timer_selection(int length);
double ptime();

void loadData(int *a, int length, int max);
void print(int *a, int length);

int selection(int *a, int n, int k);
void insert(int *s, int n, int elem);

int main(void) {
    int a[8] = {10, 30, 100, 1000, 10000, 100000, 300000, 1000000};
    int i;

    for (i = 0; i < 8; i++) {
        timer_selection(a[i]);
    }
    return 0;
}

void timer_selection(int length) {
    int k = length / 2;
    double start, end, duration;

    int *a = calloc(length, sizeof(int));
    loadData(a, length, MAX);
    start = ptime();
    selection(a, length, k);
    end = ptime();
    duration = end - start;
    printf("%10d - %10fs\n", length, duration);
}

/* **************** */
/* DATA PREPARATION */
/* **************** */

double ptime() {
    return (double) clock() / CLOCKS_PER_SEC;
}

void loadData(int *a, int length, int max) {
    int i;

    srand(time(NULL));
    for (i = 0; i < length; i++) {
        a[i] = rand() % max;
    }
}

void print(int *a, int length) {
    return;
    int i;

    printf("data: %d elems\n", length);
    for (i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/* ******** */
/* SOLUTION */
/* ******** */

// returns the k-th biggest number in n-length array a.
// scan a from start to end using a k-length array to store the k largest numbers
int selection(int *a, int n, int k) {
    int i;
    int *s = malloc(sizeof(int) * k);

    for (i = 0; i < n; i++) {
        insert(s, k, a[i]);
    }
    print(s, k);
    return s[k];
}

// insert elem to n-length array s in descent order.
void insert(int *s, int n, int elem) {
    int i, j, tmp;
    for (i = 0; i < n; i++) {
        if (s[i] < elem) {
            break;
        }
    }
    for (j = n - 1; j > i; j--) {
        s[j] = s[j - 1];
    }
    s[i] = elem;
}
