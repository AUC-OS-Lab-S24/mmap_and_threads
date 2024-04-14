#include "threads_compute.h"
#include "mmap_compute.h"
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
  
    result = mmap_compute(4, "test/numbers.txt", add);
    printf("Result: %lu\n", result);

    result = threads_compute(4, "test/numbers.txt", multiply);
    printf("Result: %lu\n", result);
  
    result = mmap_compute(4, "test/numbers.txt", multiply);
    printf("Result: %lu\n", result);
    return 0;
}

/*


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