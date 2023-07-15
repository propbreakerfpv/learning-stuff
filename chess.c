#include <stdio.h>
#include <stdlib.h>

struct Board Board;
struct Board;
struct Point;
struct Board *create_board();
void display(struct Board*);

int main(int argc, char *argv[]){

    struct Board* board = create_board();
    display(board);

    return 0;
}

struct Board {
    struct Point* xy[64];
};

struct Point {
    int x;
    int y;
};

struct Board *create_board() {
    struct Board* b = malloc(sizeof(struct Board));
    return b;
}

void display(struct Board* board) {
    char str[64+8+1];
    str[64+8] = '\0';
    for (int i = 0; i < 64; i ++) {
        switch (board->xy[i]->x * board->xy[i]->y) {
            case 0:
                str[i] = ' ';
                break;
            case 1:
                str[i] = 'p';
                break;
            case 2:
                str[i] = 'k';
                break;
            case 3:
                str[i] = 'r';
                break;
            case 4:
                str[i] = 'b';
                break;
            case 5:
                str[i] = 'K';
                break;
            case 6:
                str[i] = 'Q';
                break;
            default:
                str[i] = '?';
                break;
        }
        printf("%s", str);
        str[i*8+1] = '\n';
    }
    printf("%s\n", str);
}
