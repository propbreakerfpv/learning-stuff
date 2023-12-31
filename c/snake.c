#include <sys/time.h>
#include <time.h>
#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


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
<<<<<<< HEAD
char dbg = '.';
int score = 0;
=======
int dbg = -1;

struct timeval end, start;
>>>>>>> c8d30df6bef789072f15903c222240cb1126ec5c

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
    int tail = get_tail(head);
    // printf("this input is \"%c\"", getch());
<<<<<<< HEAD
    int ch = getch();
    switch (ch) {
        case 'w': case KEY_UP:
            dbg = 'w';
            dir = 1;
            head -= WIDTH;
            break;
        case 'a': case KEY_LEFT:
            dbg = 'a';
            dir = 0;
            head -= 1;
            break;
        case 's': case KEY_DOWN:
            dbg = 's';
            dir = 3;
            head += WIDTH;
            break;
        case 'd': case KEY_RIGHT:
            dbg = 'd';
=======
    gettimeofday(&start, 0);
    char ch = getch();
    gettimeofday(&end, 0);
    unsigned int time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    dbg = time / 1000;
    struct timespec t = {0, (time / 1000) * 1000000};
    struct timespec rem = {0, 0};

    int res;
    do{
        res = nanosleep(&t, &rem);
    } while (res && errno == EINTR);

    // sleep(2);
    switch (ch) {
        case 'w':
            dir = 1;
            head -= WIDTH;
            break;
        case 'a':
            dir = 0;
            head -= 1;
            break;
        case 's':
            dir = 3;
            head += WIDTH;
            break;
        case 'd':
>>>>>>> c8d30df6bef789072f15903c222240cb1126ec5c
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
        score ++;
        int rnum;
        do {
            rnum = rand() % WIDTH * HIGHT;
        } while (board[rnum] != EMPTY);
        board[rnum] = APPLE;
        length ++;
    } else {
        // we only do this if there isn't an apple so the snake grows
        board[tail] = EMPTY;
        snake[tail] = -1;
    }
    board[head] = HEAD;
    snake[head] = dir;
}

void display() {
    clear();
<<<<<<< HEAD
    printw("%i head %i\n", dbg, head);
=======
    printw("dbg: %i", dbg, head);
>>>>>>> c8d30df6bef789072f15903c222240cb1126ec5c
    int idx = 0;
    for (int i = 0; i < HIGHT; i ++) {
        printw("|");
        for (int j = 0; j < WIDTH; j ++) {
            printw("%c", board[idx]);
            idx ++;
        }
        printw("|\n");
    }
    printw("score %i", score);
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
