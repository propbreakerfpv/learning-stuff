#include <stdio.h>
#include <stdlib.h>
#include <time.h>

<<<<<<< HEAD
#define LEN 1000
=======
#include <ncurses.h>
#include <locale.h>

#define LEN 100
>>>>>>> c8d30df6bef789072f15903c222240cb1126ec5c


struct Square {
    int x;
    int y;
    int type;
};

void display(struct Square* board);

int main() {
    initscr();
    setlocale(LC_CTYPE, "");
    struct Square *board = malloc(sizeof(struct Square) * LEN);

    srand(time(NULL));

    for (int i = 0; i < LEN; i ++) {
        int r = rand() % (1 - 0 + 1);
        struct Square square = {i%10 + 1, i/10 + 1, r};
        board[i] = square;
    }
    display(board);

    free(board);
    getch();
    endwin();
    return 0;
}

void display(struct Square* board) {
    for (int i = 0; i < LEN; i ++) {
        move(board[i].y, board[i].x);
        if (board[i].type == 1)  {
            printw("#");
            // printf("\033[%i;%iH█", board[i].x, board[i].y);
        } else if (board[i].type == 0) {
            printw(" ");
            // printf("\033[%i;%iH ", board[i].x, board[i].y);
        } else {
            continue;
        }
    }
    printf("\n");
}
