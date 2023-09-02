#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>


#define BODY '#'
#define HEAD '8'
#define APPLE '0'
#define EMPTY ' '

#define HIGHT 20
#define WIDTH 30


void calculate_move();
void init_board();
void display();
void update();
int get_tail(int idx);

char board[600];
int head;
// 0-right, 1-down, 2-left, 3-up -1-tail
int dir;
int snake[600];
int length;
char dbg = '.';

int main(){
    // init ncurses
    initscr();
    noecho();
    wtimeout(stdscr, 500);
    keypad(stdscr, true);

    init_board();
    while(1) {
        // char ch = getch();
        calculate_move();
        // update();
        display();
    }

    return 0;
}
void calculate_move() {
    board[head] = BODY;
    // printf("this input is \"%c\"", getch());
    char ch = getch();
    switch (ch) {
        case 'w':
            dbg = 'w';
            dir = 1;
            head -= WIDTH;
            break;
        case 'a':
            dbg = 'a';
            dir = 0;
            head -= 1;
            break;
        case 's':
            dbg = 's';
            dir = 3;
            head += WIDTH;
            break;
        case 'd':
            dbg = 'd';
            dir = 2;
            head += 1;
            break;
        case -1:
            if (dir == 0) {
                head -= 1;
            } else if (dir == 1) {
                head -= WIDTH;
            } else if (dir == 2) {
                head += 1;
            } else if (dir == 3) {
                head += WIDTH;
            }
            break;
        default:
            break;
    }
    if (board[head] == APPLE) {
        int rnum = rand() % WIDTH * HIGHT;
        board[rnum] = APPLE;
        length ++;
    } else {
        // we only do this if there isn't an apple so the snake grows
        int tail = get_tail(head - 1);
        dbg = tail;
        board[tail] = EMPTY;
        snake[tail] = -1;
    }
    board[head] = HEAD;
    snake[head] = dir;
}

void display() {
    clear();
    printw("%i head %i", dbg, head);
    int idx = 0;
    for (int i = 0; i < HIGHT; i ++) {
        for (int j = 0; j < WIDTH; j ++) {
            printw("%c", board[idx]);
            idx ++;
        }
        printw("\n");
    }
}

void init_board() {
    dir = 2;
    head = 105;
    length = 6;
    for (int i = 0; i < 600; i++) {
        snake[i] = -1;
        board[i] = EMPTY;
    }
    board[100] = BODY;
    snake[100] = 2;
    board[101] = BODY;
    snake[101] = 2;
    board[102] = BODY;
    snake[102] = 2;
    board[103] = BODY;
    snake[103] = 2;
    board[104] = BODY;
    snake[104] = 2;
    board[head] = HEAD;
    snake[head] = 2;
    board[head + 2] = APPLE;
    // board[5*24 + 20] = APPLE;
}

int get_tail(int idx) {
    int dir = snake[idx];
    int res;
    if (dir == -1) {
        // dbg = dir;
        return -1;
    } else if (dir == 0) {
        res = get_tail(idx + 1);
    } else if (dir == 1) {
        res =  get_tail(idx + WIDTH);
    } else if (dir == 2) {
        res = get_tail(idx - 1);
    } else if (dir == 3) {
        res = get_tail(idx - WIDTH);
    }
    if (res == -1) {
        return idx;
    }
    return res;
}
