#include <stdio.h>

int *foo();
void bar();

int main () {
    int *a;

    a = foo();
    printf("*a: %d\n", *a);

    bar();
    printf("*a: %d\n", *a);
}

int *foo() {
    int x = 211;
    int *px = &x;
    return px;
}

void bar() {
    int z[] = { 91, 92, 93, 94 };
}
