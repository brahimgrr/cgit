#include <stdio.h>

int no = 0;

void hanoi(int, int, int, int);

int main () {
    int dim = 8;
    //numero di pioli -> 3
    hanoi(dim, 1,2,3);
    printf("\nno iter: %d\n", no);
    return 0;
}

void hanoi(int dim, int init, int support, int target) {
    no++;
    if (dim == 1) {
        printf("%d -> %d\n", init, target);
        return;
    }
    if (dim == 2) {
        printf("%d -> %d\n", init, support);
        printf("%d -> %d\n", init, target);
        printf("%d -> %d\n", support, target);
        return;
    }
    hanoi(dim - 1, init, target, support);
    hanoi(1, init, 0, target);
    hanoi(dim - 1, support, init, target);
}