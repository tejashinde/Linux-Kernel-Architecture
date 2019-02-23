#include <stdio.h>

int factorial(int i) {
    int result = i * factorial(i - 1);
    return result;
}

int main()
{
    int result = factorial(4);
    printf("result is %d", result);
}
