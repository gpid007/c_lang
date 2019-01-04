#include <stdio.h>                   // handling input output
#include <stdlib.h>                  // size_t, wchar_t, div_t, ldiv_t
#include <fcntl.h>                   // fd = open(...); file control
#include <sys/stat.h>                // return file descriptor struct 
#include <unistd.h>                  // POSIX interface for S_IRUSR ...
#include <sys/mman.h>                // mmap
#include <errno.h>                   // error number explained
#include <string.h>                  // strcpy();
#include <pthread.h>                 // thread API


/******************** PROTOTYPE ********************/
void *getArg(int argc, char *argv[]);
void *checkArg();
int fastOpen(int i);
void *fastPrint(int i);
void *fastWrite(int i);
void *fastClose(int i);
//void *fastRead(void *arg);


/******************** GLOBAL ********************/ 
// int    tArr[2];                      // Thread ID Array
char   fnArr[2][524];                // File Name
char   dArr[2][2];                   // Delimiter Array
int    fc = 0;                       // File Counter
int    dc = 0;                       // Delimiter Counter
int    fdArr[2];                     // File Descriptor Array

/******************** MAIN ********************/
int main(int argc, char *argv[])
{
    // ARGUMENT //
    getArg(argc, argv);
    checkArg();

    // VIRTUAL MEMORY //
    for (int i=0; i<fc; i++)
    {
        printf("\n%d", fastOpen(i));
    }
/*    
    // CREATE THREAD //
    for (int i=0; i<fc; i++)
    {
        pthread_t tArr[i];
        printf("\n-f %s -t %ld", fnArr[i], tArr[i]);
        pthread_create(&tArr[i], NULL, fastRead, &i);
    }
    // JOIN THREAD //
    for (int i=0; i<fc; i++)
    {
        pthread_join(tArr[i], NULL);
    }
*/
    // END //
    printf("\n");
    return 0;
}


/******************** FUNCTION ********************/ 

//////////////////// CHECK ARG ////////////////////
void *getArg(int argc, char *argv[])
{
    printf("\nGet arguments");
    for (int i=0; i<argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
                case 'f':
                {
                    strcpy(fnArr[fc], argv[i+1]);
                    fc++;
                    break;
                }
                case 'd':
                {
                    strcpy(dArr[dc], &argv[i+1][0]);
                    dc++;
                    break;
                }
            }
        }
    }
}

//////////////////// CHECK ARG ////////////////////
void *checkArg()
{
    printf("\nCheck arguments");
    for (int i=0; i<fc; i++)
    {
        printf("\n-f %s\t-d '%s'", fnArr[i], dArr[i]);
    }
    printf("\n");
}

//////////////////// FAST OPEN ////////////////////
// void *fastRead(void *arg){}
// int *iptr = (int*) arg; // Hand-Over Pointer
int fastOpen(int i)
{
    struct  stat sv;                 // Stat Variable Struct "sv"

    // OPEN //
    printf("\nOpen: %s", fnArr[i]);
    fdArr[i] = open(fnArr[i], O_RDWR, S_IRUSR | S_IWUSR);

    // ERRNO //
    if (fstat(fdArr[i], &sv) == -1)
    {
        fprintf(stderr, "\n[ERROR %i] %s", errno, strerror(errno));
        exit(-1);
    }

    // FILE SIZE & MMAP //
    printf("\nSize: %ld Bytes\n", sv.st_size); 
    
    return sv.st_size;
}    
/*

    char *pMem = mmap(NULL, sv.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdArr[i], 0);

    // PRINT FILE //
    for (int i=0; i<sv.st_size; i++)
    {
        printf("%c", pMem[i]);
    }                 

    // DEALLOCATE & CLOSE //
    munmap(pMem, sv.st_size);
    close(fdArr[i]);
}
*/
