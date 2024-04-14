#include "threads_compute.h"
#include <stdio.h>

unsigned long add(unsigned long a, unsigned long b)
{
    return a + b;
}

unsigned long multiply(unsigned long a, unsigned long b)
{
    return a * b;
}

int main()
{
    unsigned long result = threads_compute(4, "test/numbers.txt", add);
    printf("Result: %lu\n", result);

    result = threads_compute(4, "test/numbers.txt", multiply);
    printf("Result: %lu\n", result);
    return 0;
}