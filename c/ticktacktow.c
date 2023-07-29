#include <stdio.h>
#include <unistd.h>

#define PLAYED 0b00000000011111111100000000000000
#define STATE  0b11111111100000000000000000000000
#define PLAYED_OFFSET 14
#define STATE_OFFSET 23

int has_won(int board);
void display(int board);
void printb(int num);
int decode_move(int *buf, char *peace);
int move(char turn, char *peace, int board);
char get_letter(int i);


int win_states[8] = {
    0b111000000,
    0b000111000,
    0b000000111,
    0b100100100,
    0b010010010,
    0b001001001,
    0b100010001,
    0b001010100,
};

int main(){
    int board = 0;
    char buf[32];
    char turn = 'X';
    int winner;
    for (int i = 0; i < 9; i ++) {
        display(board);
        while (1) {
            printf("its %c's turn: ", turn);
            fflush(stdout);
            read(1, &buf, 32);
            int new_board = move(turn, buf, board);
            if (new_board != -1) {
                board = new_board;
                break;
            }
        }
        if (turn == 'X') {
            turn = 'O';
        } else {
            turn = 'X';
        }
        winner = has_won(board);
        if (winner != -1) {
            break;
        }
    }
    display(board);
    if (winner == 1) {
        printf("X has won the game!\n");
    } else if (winner == 0) {
        printf("O has won the game!\n");
    } else {
        printf("draw\n");
    }
    // board = move("a1", board);
    // display(board);
    return 0;
}


int has_won(int board) {
    int state = (board & STATE) >>  STATE_OFFSET;
    int played = (board & PLAYED) >>  PLAYED_OFFSET;

    int count = 0;
    int s = state ^ played;
    for (int i = 0; i < 8; i++) {
        if ((s & win_states[i]) == win_states[i]) {
            return 0;
        }
    }
    s = state;
    for (int i = 0; i < 8; i++) {
        if ((s & win_states[i]) == win_states[i]) {
            return 1;
        }
    }
    return -1;
}

int move(char turn, char *peace, int board) {
    int buf[2];
    int ret = decode_move(buf, peace);
    if (ret == -1) {
        return -1;
    }
    int state = 0;
    if (turn == 'X') {
        state = 0b00000000100000000000000000000000 << (buf[1] + (buf[0] * 3));
    }
    int played = 0b00000000000000000100000000000000 << (buf[1] + (buf[0] * 3));

    if ((board & PLAYED) & played) {
        return -1;
    }

    board = (board | state) | played;
    return board;
}

int decode_move(int *buf, char *peace) {
    switch (peace[0]) {
        case 'a':
            buf[0] = 0;
            break;
        case 'b':
            buf[0] = 1;
            break;
        case 'c':
            buf[0] = 2;
            break;
        default:
            return -1;
    }
    switch (peace[1]) {
        case '1':
            buf[1] = 0;
            break;
        case '2':
            buf[1] = 1;
            break;
        case '3':
            buf[1] = 2;
            break;
        default:
            return -1;
    }
    return 1;
}

//  state(x or o)         played
// 111 1,11 11,1  11,1 111, 111, 0000, 0000, 0000

void display(int board) {
    int played = (board & PLAYED) >> PLAYED_OFFSET;
    int state = (board & STATE) >> STATE_OFFSET;
    printf("    1   2   3\n");
    for (int i = 0; i < 3; i ++) {
        printf(" %c:", get_letter(i));
        for (int j = 0; j < 3; j ++) {
            if (! (played & 1)) {
                printf("   ");
            } else {
                if (state & 1) {
                    printf(" X ");
                } else {
                    printf(" O ");
                }
            }
            state = (state >> 1) & 0xefffffff;
            played = (played >> 1) & 0xefffffff;
            if (j == 2) {
                break;
            }
            printf("|");
        }
        if (i == 2) {
            break;
        }
        printf("\n   ---+---+---\n");
    }
    printf("\n\n");
}

void printb(int num) {
    for (int i = 0; i < sizeof(int) * 8; i++) {
        if (num & 1) {
            printf("1");
        } else {
            printf("0");
        }
        num = (num >> 1) & 0xefffffff;
    }
}

char get_letter(int i) {
    switch (i) {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
    }
    return '\0';
}
