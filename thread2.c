#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int* pThrdIdArr[1];

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
    pthread_t pThrdIdArr[0];
    int v = 5;
    pthread_create(&pThrdIdArr[0], NULL, threadA, &v);
    
    pthread_t threadIdB;
    pthread_create(&threadIdB, NULL, &threadB, NULL);
    
    pthread_join(pThrdIdArr[0], NULL);
    printf("\nthread's done: v=%d", v);
    pthread_join(threadIdB, NULL);

    printf("\n");
    return 0;
}
