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
void *fastOpen(int i);


/******************** GLOBAL ********************/ 
struct File 
{
    char    name[256];
    char    delim[2];
    int     fd;
    int     size;
    int     id;
} fSuct[2];

struct stat st;


/******************** MAIN ********************/
int main(int argc, char *argv[])
{
    // ARGUMENT //
    getArg(argc, argv);
    
    for (int i=0; i<2; i++)
    {
        fastOpen(i);    
    }

    return 0;
}


/******************** FUNCTION ********************/ 

//////////////////// CHECK ARG ////////////////////
void *getArg(int argc, char *argv[])
{
    int f = 0;
    int d = 0;

    for (int i=0; i<argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
                case 'f':
                {
                    strcpy(fSuct[f].name, argv[i+1]);
                    stat(argv[i+1], &st);
                    fSuct[f].size = st.st_size;
                    f++;
                    break;
                }
                case 'd':
                {
                    strcpy(fSuct[d].delim, &argv[i+1][0]);
                    d++;
                    break;
                }
            }
        }
    }
}

//////////////////// FAST ALLOCATE ////////////////////
void *fastOpen(int i)
{
    // OPEN //
    fSuct[i].fd = open(fSuct[i].name, O_RDWR, S_IRUSR | S_IWUSR);

    // ERROR //
    if (fstat(fSuct[i].fd, &st) == -1)
    {
        fprintf(stderr, "\n[ERR %i] %s", errno, strerror(errno));
        exit(-1);
    }

    // ALLOCATE //
    char *pMem = mmap(
        NULL, fSuct[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, 
        fSuct[i].fd, 0
    );

    // PRINT FILE //
    printf("\nPrint %s\n", fSuct[i].name);
    for (int j=0; j<fSuct[i].size; j++)
    {
        printf("%c", pMem[j]);
    }                 

    // DEALLOCATE & CLOSE //
    munmap(pMem, fSuct[i].size);
    close(fSuct[i].fd);
}
