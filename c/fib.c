#include <stdio.h>
int main(){
    int x, y, z;
    while (x < 0xffff) {
        printf("%i\n", x);

        z = x + y;
        x = y;
        y = z;
    }
    return 0;
}
