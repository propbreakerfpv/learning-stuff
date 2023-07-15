#include <stdio.h>

#define BLACK 8
#define WHITE 16
#define NONE 0
#define PAWN 1
#define ROOK 2
#define KNIGHT 3
#define BISHOP 4
#define QUEEN 5
#define KING 6



// 1 is white 2 is black
unsigned char currentTurn = 1;
unsigned char board[64] = {
    (BLACK | ROOK), (BLACK | KNIGHT), (BLACK | BISHOP), (BLACK | QUEEN), (BLACK | KING), (BLACK | BISHOP), (BLACK | KNIGHT), (BLACK | ROOK),
    (BLACK | PAWN), (BLACK | PAWN), (BLACK | PAWN), (BLACK | PAWN), (BLACK | PAWN), (BLACK | PAWN), (BLACK | PAWN), (BLACK | PAWN),
    (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE),
    (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE),
    (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE),
    (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE), (BLACK | NONE),
    (WHITE | PAWN), (WHITE | PAWN), (WHITE | PAWN), (WHITE | PAWN), (WHITE | PAWN), (WHITE | PAWN), (WHITE | PAWN), (WHITE | PAWN),
    (WHITE | ROOK), (WHITE | KNIGHT), (WHITE | BISHOP), (WHITE | QUEEN), (WHITE | KING), (WHITE | BISHOP), (WHITE | KNIGHT), (WHITE | ROOK),
};


void draw_board();
char *piece_lookup(unsigned char piece, int x, int y);
unsigned char get_piece_at(int x, int y);
void move(int from_x, int from_y, int to_x, int to_y);

int main() {
    // printf("%i\n", NONE | BLACK);
    draw_board();
    move(3, 7, 0, 0);

    return 0;
}
char *piece_lookup(unsigned char piece, int x, int y) {
    char *color;
        switch (piece) {
            case NONE | WHITE:
                if ((x + y) % 2 == 0) {
                    color = "\33[38;5;238m*\33[0m";
                } else {
                    color = "\33[38;5;244m*\33[0m";
                }
                break;
            case NONE | BLACK:
                if ((x + y) % 2 == 0) {
                    color = "\33[38;5;238m*\33[0m";
                } else {
                    color = "\33[38;5;244m*\33[0m";
                }
                break;
            case PAWN | WHITE:
                color = "\33[37mp\33[0m";
                break;
            case ROOK | WHITE:
                color = "\33[37mr\33[0m";
                break;
            case BISHOP | WHITE:
                color = "\33[37mb\33[0m";
                break;
            case KNIGHT | WHITE:
                color = "\33[37mk\33[0m";
                break;
            case QUEEN | WHITE:
                color = "\33[37mQ\33[0m";
                break;
            case KING | WHITE:
                color = "\33[37mK\33[0m";
                break;
            case PAWN | BLACK:
                color = "\33[31mp\33[0m";
                break;
            case ROOK | BLACK:
                color = "\33[31mr\33[0m";
                break;
            case BISHOP | BLACK:
                color = "\33[31mb\33[0m";
                break;
            case KNIGHT | BLACK:
                color = "\33[31mk\33[0m";
                break;
            case QUEEN | BLACK:
                color = "\33[31mQ\33[0m";
                break;
            case KING | BLACK:
                color = "\33[31mK\33[0m";
                break;
            default:
                color = "\33[38;5;238m*\33[0m";
                break;
        }
    return color;
}

void move(int from_x, int from_y, int to_x, int to_y) {
    int piece = get_piece_at(from_x, from_y);
    int type = piece & 0b00111;
    int color = piece & 0b11000;
    switch (type) {
        case 0:
            // no piece to move
            return;
        case KING:
            move_king(from_x, from_y, to_x, to_y);
            break;
    }
}

unsigned char get_piece_at(int x, int y) {
    return board[x + (y * 8)];
}

void draw_board() {
    printf("   ");
    for (int i = 0; i < 8; i ++) {
        printf("%d ", i);
    }
    int y = 0;
    for(int x = 0; x < 64; x ++){
        if (x % 8 == 0) {
            // int rank = ;
            printf("\n%d: ", (x / 8));
            y ++;
        }
        printf("%s", piece_lookup(board[x], x, y));
        printf(" ");
    }
    printf("\n");
}

