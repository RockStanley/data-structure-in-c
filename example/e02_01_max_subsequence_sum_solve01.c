// [2020-06-30 23:13:17]
// [2020-06-30 23:35:37]
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a[] = {4, -3, 5, -2, -1, 2, 6, -2};

    printf("%d\n", maxSubsequenceSum(a, 0, 8));
    return 0;
}

// start included, end excluded
int maxSubsequenceSum(int *a, int start, int end) {
    int leftmaxsum, rightmaxsum, middlemaxsum;
    int lhsum, lhmax, rhsum, rhmax;
    int i;
    int pivot = (start + end) / 2;

    if (end - start == 1) {
        return a[start];
    } else {
        leftmaxsum = maxSubsequenceSum(a, start, pivot);
        rightmaxsum = maxSubsequenceSum(a, pivot, end);
        for (i = pivot - 1, lhsum = 0, lhmax = 0; i >= start; i--) {
            lhsum += a[i];
            lhmax = lhmax < lhsum ? lhsum : lhmax;
        }
        for (i = pivot, rhsum = 0, rhmax = 0; i < end; i++) {
            rhsum += a[i];
            rhmax = rhmax < rhsum ? rhsum : rhmax;
        }
        middlemaxsum = 0;
        if (lhmax >= 0) {
            middlemaxsum += lhmax;
        }
        if (rhmax >= 0) {
            middlemaxsum += rhmax;
        }
        return max3(leftmaxsum, rightmaxsum, middlemaxsum);
    }
}

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

int max(int a, int b) {
    return a > b ? a : b;
}