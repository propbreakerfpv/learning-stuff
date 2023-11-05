#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100


struct Square {
    int x;
    int y;
    int type;
};

void display(struct Square* board);

int main() {
    struct Square *board = malloc(sizeof(struct Square) * LEN);

    srand(time(NULL));

    for (int i = 0; i < LEN; i ++) {
        int r = rand() % (1 - 0 + 1);
        struct Square square = {i%10 + 1, i/10 + 1, r};
        board[i] = square;
    }
    display(board);

    free(board);
    return 0;
}

void display(struct Square* board) {
    for (int i = 0; i < LEN; i ++) {
        // printf("board[i]: %i, %i, %i\n", board[i].x, board[i].y, board[i].type);
        if (board[i].type == 1)  {
            printf("\033[%i;%iH█", board[i].x, board[i].y);
        } else if (board[i].type == 0) {
            printf("\033[%i;%iH ", board[i].x, board[i].y);
        } else {
            continue;
        }
    }
    printf("\n");
}
