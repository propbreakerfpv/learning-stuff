#include <stdio.h>
#include <stdbool.h>


// printf("\033[%i;%iH\033[30m█", pos_y, pos_x);
// printf("\033[%i;%iH\033[30m\n", hight, width);
// printf("\033[%i;%iH\033[31m█", pos_y, pos_x);
int main(int argc, char *argv[]){
    printf("\033[2J");

    return 0;
}

