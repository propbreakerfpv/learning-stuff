#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 64

#define true 1
#define false 0

void play();
int is_guess(int guess);
int is_higher();
int read_with_prompt(char* prompt, void* buf, int len);


int main(){
    play();
    return 0;
}

void play() {
    char buf[BUF_SIZE];

    int count = 0;
    int guess = 50;
    int top = 100;
    int bot = 0;

    printf("think of a number between 0 and 100.");

    while(true) {
        count ++;

        if (is_guess(guess)) {
            break;
        }

        if (is_higher()) {
            bot = guess + 1;
        } else {
            top = guess - 1;
        }

        guess = ((top - bot) / 2) + bot;

        if (bot == top) {
            break;
            guess = bot + 1;
        }
    }
    printf("your number is %i! and it took %i guesses to find it\n", guess, count);
}

int is_guess(int guess) {
    char buf[BUF_SIZE];
    while (true) {
        printf("is the number %i? yes(y) no(n)", guess);
        read_with_prompt(" ", &buf, BUF_SIZE);

        if (buf[0] == 'y') {
            return true;
        } else if (buf[0] == 'n') {
            return false;
        } else {
            printf("invalid input\n");
        }
    }
}

int is_higher() {
    char buf[BUF_SIZE];

    while (true) {
        read_with_prompt("is the number higher(h) or lower(l)?", &buf, BUF_SIZE);
        if (buf[0] == 'h') {
            return true;
        } else if (buf[0] == 'l') {
            return false;
        } else {
            printf("invalid input\n");
        }
    }
}

int read_with_prompt(char* prompt, void* buf, int len) {
    printf("%s", prompt);

    fflush(stdout);

    return read(1, buf, len);
}
