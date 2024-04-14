#include "mmap_compute.h"
#include <stdio.h>

unsigned long add(int a, int b)
{
    return a + b;
}

unsigned long multiply(int a, int b)
{
    return a * b;
}

int main()
{
    unsigned long result = mmap_compute(4, "test/numbers.txt", add);
    printf("Result: %lu\n", result);

    result = mmap_compute(4, "test/numbers.txt", multiply);
    printf("Result: %lu\n", result);
    return 0;
}
