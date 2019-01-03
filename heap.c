#include <stdlib.h>
#include <stdio.h>

int main()
{
    int x, y;

    printf("\nOpen a system monitor (task manager)!");
    printf("\n\t1 integer =  %zu Bytes", sizeof(int));
    printf("\nHow many GB to allocate for integers?\n");
    scanf(" %d", &x);

    y = x * 1e9 / sizeof(int);
    printf("\nAllocating %d integers = %d GB to heap.", y, x);

    int *pInt; 
    pInt = (int*) malloc(y * sizeof(int)); 
    if (!pInt)
    {
        printf("\npInt heap allocation failed!");
        return 1;
    }

    for (int i=0; i<y; i++)
    {
        pInt[i] = i -i -i;
    }

    printf("\nCheck your RAM!\nEntry 100: %d\nENTER to free heap.", pInt[100]); 
    getchar(); 
    getchar();

    free(pInt);

    printf("\nENTER to exit.\n");
    getchar();

    return 0;
}
