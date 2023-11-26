#include <stdlib.h>
#include <stdio.h>

#define LEN 10

struct Square { 
    int x; 
    int y;
    int type; 
};

int main(){
    struct Square* board = malloc(sizeof(struct Square) * LEN);


    for (int i = 0; i < LEN; i ++) {
        board[i].x = 1;
        board[i].y = 2;
        board[i].type = 3;
    }



    

    return 0;
}
