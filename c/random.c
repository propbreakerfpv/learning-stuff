
int main(int argc, char const *argv[])
{
    int test = 0;
    printf("%i\n", test);
    test = test ^ (1 << 31);
        printf("%i\n", test);
test = test ^ (1 << 31);
        printf("%i\n", test);
    return 0;
}
