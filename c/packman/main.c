#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../terminal_helper/terminal_helper.h"

#define LEN 100
#define PLAYER '*'

// struct termios orig_termios;
int WIDTH = 10;
int HIGHT = 10;

typedef struct {
    int x;
    int y;
    int type;
} Square;

typedef struct {
    int x;
    int y;
} Player;

int get_type(char ch) {
    switch (ch) {
        case ' ':
            return 0;
        case '#':
            return 1;
        default:
            return -1;
    }
}

Square* create_board(char* level) {
    Square *board = malloc(sizeof(Square) * LEN);

    FILE *f = fopen("level.lvl", "r");
    char str[255];

    int idx = 0;
    while (fgets(str, 255, f)) {
        for (int i = 0; i < 10; i ++) {
            Square square = {idx/10 + 1, idx%10 + 1, get_type(str[i])};
            board[idx] = square;
            idx ++;
        }
    }

    fclose(f);
    return board;
}

void display_board(Square *board) {
    for (int i = 0; i < LEN; i ++) {
        if (board[i].type == 1)  {
            printf("\033[%i;%iH█", board[i].x, board[i].y);
        } else if (board[i].type == 69) {
            printf("\033[%i;%iH\033[31m█\033[0m", board[i].x, board[i].y);
        } else if (board[i].type == 0) {
            printf("\033[%i;%iH ", board[i].x, board[i].y);
        } else {
            continue;
        }
    }
    printf("\n\033[%i;1H", HIGHT + 1);
}

void display_player(Player *player) {
    printf("\033[%i;%iH%c\033[%i;1H", player->x, player->y, PLAYER, HIGHT + 1);
    fflush(stdout);
}

//  char read_timeout() {
//     struct timeval tv;
//     fd_set fds;
//     tv.tv_sec = 1;
//     tv.tv_usec = 0;
//
//     FD_ZERO(&fds);
//     FD_SET(STDIN_FILENO, &fds);
//
//     select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
//
//     if (FD_ISSET(STDIN_FILENO, &fds) != 0) {
//         char buf[1];
//         read(STDIN_FILENO, &buf, 1);
//         // printf("read: %c\n", buf[0]);
//         return buf[0];
//     }
//     return -1;
// }
//
// void disable_raw_mode() {
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
// }
//
// void enable_raw_mode() {
//     tcgetattr(STDIN_FILENO, &orig_termios);
//     atexit(disable_raw_mode);
//
//     struct termios raw = orig_termios;
//     raw.c_lflag &= ~(ECHO | ICANON);
//
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
// }

void clear_scr() {
    printf("\033[2J");
}

int move_player(int x, int y, Square *board, Player *player) {
    for (int i = 0; i < LEN; i ++) {
        // printf("idx: %i\n", i);
        // usleep(100000);
        if (board[i].x == x && board[i].y == y) {
            // sleep(1);
            if (board[i].type == 0) {
                printf("\033[%i;%iH \033[%i;1H", player->x, player->y, HIGHT + 1);
                player->x = x;
                player->y = y;
                display_player(player);
                return 1;
            } else {
                return 0;
            }
        } else {
            // int type = board[i].type;
            // board[i].type = 69;
            // display_board(board);
            // board[i].type = type;
        }

    }
    return -1;
}

int main() {
    enable_raw_mode();
    clear_scr();

    Square* board = create_board("level.lvl");
    Player player = {2, 2};
    display_board(board);
    
    display_player(&player);

    // sleep(2);

    while(1) {
        switch (read_timeout(500)) {
            case 'k':
                move_player(player.x - 1, player.y, board, &player);
                break;
            case 'j':
                move_player(player.x + 1, player.y, board, &player);
                break;
            case 'h':
                move_player(player.x, player.y - 1, board, &player);
                break;
            case 'l':
                move_player(player.x, player.y + 1, board, &player);
                break;
            default:
                break;
        }
    }

    free(board);
}
