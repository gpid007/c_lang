#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* threadA(void* arg)
{
    int* iptr = (int*) arg;
    for (int i=0; i<5; i++)
    {
        printf("\nA %d %d", i, *iptr);
        sleep(1);
        (*iptr)++;
    }
    return NULL;
}

void* threadB(void* arg)
{
    for (int i=0; i<4; i++) 
    {
        printf("\nB %d", i);
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t threadIdA;
    int v = 5;
    pthread_create(&threadIdA, NULL, threadA, &v);
    
    pthread_t threadIdB;
    pthread_create(&threadIdB, NULL, &threadB, NULL);
    
    pthread_join(threadIdA, NULL);
    printf("\nthread's done: v=%d", v);
    pthread_join(threadIdB, NULL);

    printf("\n");
    return 0;
}
