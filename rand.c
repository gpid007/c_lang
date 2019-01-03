#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    int x; 
    time_t t;
    srand((unsigned) time(&t));
    
    while (1)
    {
        printf("\nRandom range [1:_]");
        scanf(" %d", &x);
        printf("%d\n", rand() % x);
    }
    
    return 0;
}
