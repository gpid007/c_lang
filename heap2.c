#include <stdio.h>
#include <stdlib.h>

int main()
{
    int GB, SC, i;
    float N;
    // Define pointer integer (array)
    int* pIntArr;

    printf("\nEnter heap allocation GB ");
    scanf(" %d", &GB);

    // Calculate number of integers
    N = (float)GB * 1e9 / sizeof(int);

    // Declare memory allocation to pointer integer array
    pIntArr = (int*) malloc((int)N * sizeof(int));
    for (i=0; i<N; i++)
    {
        // Assign integers to array in heap memory
        pIntArr[i] = i * i;
    }

    printf("\nWhich subscript to inspect? ");
    scanf(" %d", &SC);
    printf("\n%d", pIntArr[SC]);

    printf("\nFreeing heap <ENTER>");
    getchar();
    getchar();
    // Freeing heap
    free(pIntArr);

    printf("\n<ENTER>");
    getchar();

    return 0;
}
