#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

struct timeval stop, start;

int main() {
    gettimeofday(&start, 0);
    sleep(5);
    for(int i = 0; i < 100000; i++) {
        printf("");
    }
    gettimeofday(&stop, 0);
    unsigned int mili = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    printf("%u\n", mili);
}
