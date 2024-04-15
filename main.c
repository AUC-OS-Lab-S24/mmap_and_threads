#include "test_increasing_N.h"
#include "test_increasing_parallelism.h"
#include <stdio.h>

#define MYCORES 4
#define MAX_PARALLELISM 2
#define BIG_N   7420

int main(int argc, char *argv[])
{
    for (int i = 0; i < 5; i++)
    {
        test_increasing_parallelism(MAX_PARALLELISM , BIG_N, argc, argv, i);
        test_increasing_N(100, 10000, 1000, MYCORES - 2, argc, argv, i);
    }

    return 0;
}
