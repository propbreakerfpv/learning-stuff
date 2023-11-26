#include <unistd.h>
#include <stdio.h>


int main(){

    char buf[64];
    read(1, &buf, 64);

    if (buf[0] == 'h'){
        printf("%s", buf);
    }


    return 0;
}
