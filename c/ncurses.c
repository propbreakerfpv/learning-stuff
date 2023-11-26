#include<curses.h>
#include<stdio.h>
#include<ncurses.h>

void checkArrow(){
    int ch;

    initscr();
    // raw();
    keypad(stdscr, TRUE);
    wtimeout(stdscr, 1000);
    noecho();

    while (1) {
        clear();
        char ch = getch();
        if (ch == KEY_UP) { // KEY_UP
            break;
        }
        printw("l");
        printw("o");
        printw("o");
        printw("p");
        printw("\n");
        // printw("loop\n");
    }

    // printw("Press q to Exit\t");

    // do{
    //     switch(ch){
    //         case KEY_UP: {
    //             printw("\n\nUp Arrow\n");
    //             printw("Press q to Exit\t");
    //             break;
    //         }
    //         case KEY_DOWN:{
    //             printw("\n\nDown Arrow\n");
    //             printw("Press q to Exit\t");
    //             break;
    //         }
    //         case KEY_LEFT:{
    //             printw("\n\nLeft Arrow\n");
    //             printw("Press q to Exit\t");
    //             break;
    //         }
    //         case KEY_RIGHT:{
    //             printw("\n\nRight Arrow\n");
    //             printw("Press q to Exit\t");
    //             break;
    //         }
    //     }
    // }while((ch = getch()) != 'q');
    //
    // printw("\n\n\t\t\t-=GoodBye=-!\n");
    refresh();
    endwin();
}

void test() {
    printf("%c", getch());
}

int main() {
    initscr();
    printw("hello");
    checkArrow();
    // test();
    endwin();
    return 0;
}
