#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* threadA(void* arg)
{
    for (int i=0; i<5; i++)
    {
        printf("\nA %d", i);
        sleep(1);
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
    pthread_create(&threadIdA, NULL, &threadA, NULL);
    
    pthread_t threadIdB;
    pthread_create(&threadIdB, NULL, &threadB, NULL);
    
    pthread_join(threadIdA, NULL);
    pthread_join(threadIdB, NULL);

    printf("\n");
    return 0;
}
