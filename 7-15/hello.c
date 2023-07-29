#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int a = 10;
    int b = 4;
    int c = add(a, b);
    float d = 6.4;
    printf("hello world\n%i, %f\n", c, d);

    int condetion = 1;
    int i = 0;
    while (condetion){
        printf("%i\n", i);
        i ++;
    }
    for (int i = 0; i < 10; i ++) {
        printf("%i\n", i);
    }
    
    return 0;
}

