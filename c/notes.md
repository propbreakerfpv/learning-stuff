# 8-27
- github/git
- talk pointers. make a funtion that takes and returns a string. talk dangling pointers
```c
int x = 4; // x is 4
int *px = &x; // px is a pointer to x
int y = *px; // y is 4, the value stored at px
```