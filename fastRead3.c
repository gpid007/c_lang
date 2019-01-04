#include <stdio.h>                   // handling input output
#include <stdlib.h>                  // size_t, wchar_t, div_t, ldiv_t
#include <fcntl.h>                   // fd = open(...); file control
#include <sys/stat.h>                // return file descriptor struct 
#include <unistd.h>                  // POSIX interface for S_IRUSR ...
#include <sys/mman.h>                // mmap
#include <errno.h>                   // error number explained
#include <string.h>                  // handling strings
#include <pthread.h>                 // thread API


/******************** PROTOTYPE ********************/
void *fastRead(void *arg);


/******************** MAIN ********************/
int main(int argc, char *argv[])
{
    int     tArr[1];                 // Thread ID Array
    int     fdArr[1];                // File Desrciptor Array
    int     result[1];               // Result Array
    char    delim;                   // Delimiter
    int     tc = 0;                  // Thread Counter
    struct  stat sv;                 // Struct: Stat Variable "sv"   

    printf("\nCHECKING ARGUMENTS...");
    for (int i=0; i<argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
                case 'f':
                {
                    // Get File Descriptor //
                    printf("\nOpen file: %s", argv[i+1]); 
                    fdArr[tc] = open(argv[i+1], O_RDWR, S_IRUSR | S_IWUSR);
                    
                    // Error Message //
                    if (fstat(fdArr[tc], &sv) == -1)
                    {
                        fprintf(stderr, "\n[ERROR %i] %s", errno, strerror(errno));
                        exit(-1);
                    }
                    
                    // Assign Thread
                    printf("\nFile size: %ld Bytes", sv.st_size); 
                    pthread_t tArr[tc];
                    pthread_create(&tArr[tc], NULL, fastRead, &fdArr[tc]);
                    
                    tc++;
                    break;
                }
                case 'd':
                {
                    delim = argv[i+1][0];
                    printf("Delimiter %s", &delim);
                    break;
                }
            }
        }
    }

    for (int i=0; i<tc; i++)
    {
        pthread_join(tArr[i], NULL); 
    }
     
    printf("\n");
    return 0;
}


/******************** FUNCTION ********************/ 

//////////////////// FAST READ ////////////////////
void *fastRead(void *fdArrTC)
{
    char    *pMem;                   // In Memory Pointer to File Content
    int     *fd = (int*) fdArrTC;    // File Descriptor for Thread Function
    struct  stat sv;                 // Struct: Stat Variable "sv"
    
    // Read to Memory //
    printf("\nRUNNING THREAD...");
    fstat(*fd, &sv);
    pMem = mmap(NULL, sv.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    for (int i=0; i<sv.st_size; i++)
    {
        printf("%c", pMem[i]);
    }    

    // Close File //    
    munmap(pMem, sv.st_size);
    
    close(*fd);
}
