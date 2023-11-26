int main(){
    int x = 5; // x in 5
    int* px = &x; // px points to x
    int y = *px; // y is 5

    //{'g', 'i',}

    char* hello = pizza("give me pizza");
    printf("%s", hello);

    return 0;
}

int pizza(char* str) {  // 105, 106
    printf("%s", str);
    return &"hello";
}

