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

/*

For improvement:
This implementation is faster for reading files directly into memory, despite potential overhead from memory reallocation.
Used code: Essentially O(2n) due to reading the file twice—first to count the items and then to read them into an array. Simplified to O(n).
Second code: O(n) because it processes each item exactly once during the reading and storing operation.

 int *read_data(const char *filepath, int *size)
{
    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        printf("Failed to open fileeeee\n");
        return NULL;
    }

    int *data = NULL;
    *size = 0;
    int number;
    char delimiter;

    while (fscanf(file, "%d%c", &number, &delimiter) != EOF)
    {
        int *temp = realloc(data, sizeof(int) * (*size + 1));
        if (!temp)
        {
            printf("Failed to allocate memory\n");
            fclose(file);
            return NULL;
        }
        data = temp;
        data[*size] = number;
        (*size)++;

        if (delimiter != ',')
        {
            break;
        }
    }

    fclose(file);
    return data;
}



*/
