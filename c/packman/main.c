#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <time.h>

#include "../terminal_helper/terminal_helper.h"

#define LEN 100
#define MOVE_HISTORY_LEN 20

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
} Location;

typedef struct {
    int x;
    int y;
    char symbol;
    Location move_history[MOVE_HISTORY_LEN];
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
            Square square = {idx%10 + 1, idx/10 + 1, get_type(str[i])};
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
            printf("\033[%i;%iH█", board[i].y, board[i].x);
        } else if (board[i].type == 69) {
            printf("\033[%i;%iH\033[31m█\033[0m", board[i].x, board[i].y);
        } else if (board[i].type == 0) {
            printf("\033[%i;%iH ", board[i].y, board[i].x);
        } else {
            continue;
        }
    }
    printf("\n\033[%i;1H", HIGHT + 1);
}

void display_player(Player *player) {
    printf("\033[%i;%iH%c\033[%i;1H", player->y, player->x, player->symbol, HIGHT + 1);
    fflush(stdout);
}

void clear_scr() {
    printf("\033[2J");
    fflush(stdout);
}

void player_move_history_push(int x, int y, Player *player) {
    for (int i = MOVE_HISTORY_LEN - 2; i > 0; i --) {
        player->move_history[i] = player->move_history[i + 1];
    }
    Location loc = {x, y};
    player->move_history[0] = loc;
}

int player_move_history_has(int x, int y, Player *player) {
    for (int i = 0; i < MOVE_HISTORY_LEN; i ++) {
        if (player->move_history[i].x == x && player->move_history[i].y == y) {
            return 1;
        }
    }
    return 0;
}

int move_player(int x, int y, Square *board, Player *player) {
    for (int i = 0; i < LEN; i ++) {
        if (board[i].x == x && board[i].y == y) {
            if (board[i].type == 0) {
                printf("\033[%i;%iH \033[%i;1H", player->y, player->x, HIGHT + 1);
                player_move_history_push(player->x, player->y, player);
                player->x = x;
                player->y = y;
                display_player(player);
                return 1;
            } else {
                return 0;
            }
        }
    }
    return -1;
}

Square *board_xy(int x, int y, Square *board) {
    return &board[(y * WIDTH + x) - 1];
}

void update_ai(Player * ai, Square *board) {
    printf("player pos %i %i.", ai->x, ai->y);
    Location movable[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    int moved = 4;
    for (int i = 0; i < LEN; i ++) {
        if (board[i].x == ai->x + 1 && board[i].y == ai->y && board[i].type == 0) {
            movable[0].x = ai->x + 1;
            movable[0].y = ai->y;
            moved --;
        }else if (board[i].x == ai->x - 1 && board[i].y == ai->y && board[i].type == 0) {
            movable[1].x = ai->x - 1;
            movable[1].y = ai->y;
            moved --;
        }else if (board[i].x == ai->x && board[i].y == ai->y + 1 && board[i].type == 0) {
            movable[2].x = ai->x;
            movable[2].y = ai->y + 1;
            moved --;
        }else if (board[i].x == ai->x && board[i].y== ai->y - 1 && board[i].type == 0) {
            movable[3].x = ai->x;
            movable[3].y = ai->y - 1;
            moved --;
        }
        if (moved == 0) {
            break;
        }
    }
    int counter = 0;
    moved = 0;
    while(1) {
        int r = rand() % 4;
        if (! player_move_history_has(movable[r].x, movable[r].y, ai) && movable[r].x != 0) {
            move_player(movable[r].x, movable[r].y, board, ai);
            moved = 1;
            break;
        }
        if (counter > 10) {
            break;
        }
        counter ++;
    }

    if (! moved) {
        while(1) {
            int r = rand() % 4;
            printf("er: %i", r);
            if (movable[r].x != 0) {
                move_player(movable[r].x, movable[r].y, board, ai);
                break;
            }
        }
    }
    display_player(ai);
}

int main() {
    srand(time(NULL));
    enable_raw_mode();
    clear_scr();

    Square* board = create_board("level.lvl");
    Player player = {2, 2, '*', {{2, 2}}};
    Player ai = {2, 2, '#', {{2, 2}}};

    display_board(board);
    
    display_player(&player);

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
        update_ai(&ai, board);
    }

    free(board);
}
