#include <stdio.h>
#include <string.h>

#define DIM 8

//knight path problem, simple heuristic approach

int search(int [DIM][DIM], int, int, int);
int isBoardFull(int [DIM][DIM]);
int possible(int [DIM][DIM], int [DIM][DIM]);
int minroute(int [DIM][DIM], int, int);
int printboard(int [DIM][DIM]);

int main () {
    int board[DIM][DIM] = {0};
    int startX, startY;

    do {
        printf("insert row (1-8): ");
        scanf("%d", &startX);
        startX--;
        printf("insert column (1-8): ");
        scanf("%d", &startY);
        startY--;
    } while (startX >= DIM || startY >= DIM || startX < 0 || startY < 0);

    printf("start -> (%d,%d)\n", (startX + 1), (startY + 1));
    int roots;
    roots = search(board, startX, startY, 0);
    if (roots == 0) {
        printf("no way");
    }
    else {
        printf("Solution Found!\n");
    }
    return 0;
}
int isBoardFull(int board[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}
int printboard(int board[DIM][DIM]) {
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            if (board[i][j] != 0) {
                printf("\033[0;32m");
            }
            printf("%2d ", board[i][j]);
            printf("\033[0m");
        }
        printf("\n");
    }
}
int possible(int board[DIM][DIM], int arr[DIM][DIM]) {
    int vertical[]   = {2, 2, -2, -2, 1, -1,  1, -1};
    int horizontal[] = {1,-1 , 1, -1, 2,  2, -2, -2};
    int min = 0;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (board[i][j] == 0) {
                for (int k = 0; k < DIM; k++) {
                    int x = i+ vertical[k];
                    int y = j+ horizontal[k];
                    if (x < DIM && y < DIM && x >= 0 && y >= 0) {
                        if (board[x][y] == 0) {
                            arr[x][y] = arr[x][y] + 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
int minroute(int arr[DIM][DIM], int px, int py) {
    int vertical[]   = {2, 2, -2, -2, 1, -1,  1, -1};
    int horizontal[] = {1,-1 , 1, -1, 2,  2, -2, -2};
    int min = 8;
    int index = 0;
    for (int k = 0; k < DIM; k++) {
        int x = px + vertical[k];
        int y = py + horizontal[k];
        if (x < DIM && y < DIM && x >= 0 && y >= 0) {
            if (arr[x][y] == 0) {
                continue;
            }
            else if (arr[x][y] <= min) {
                min = arr[x][y];
                index = k;
            }
        }
    }
    return index;
}

int search(int Pboard[DIM][DIM], int x, int y, int c) {
    int vertical[]   = {2, 2, -2, -2, 1, -1,  1, -1};
    int horizontal[] = {1,-1 , 1, -1, 2,  2, -2, -2};
    int mindex, res = 0;
    int board[DIM][DIM];
    int priority[DIM][DIM] = {0};

    memcpy(board, Pboard, sizeof(int) * (DIM * DIM));

    possible(board, priority);

    if (board[x][y] != 0) {
        if (isBoardFull(board)) {
            printf("DONE\n");
            printboard(board);
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        c++;
        board[x][y] = c;
        priority[x][y] = 0;
    }
    mindex = minroute(priority, x, y);
    return search(board, x + vertical[mindex], y + horizontal[mindex], c);
}