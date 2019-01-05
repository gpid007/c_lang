#include <stdio.h>       // handling I/O
#include <stdlib.h>      // exit(-1), size_t
#include <fcntl.h>       // file control    --fd
#include <sys/stat.h>    // file descriptor --fd
#include <unistd.h>      // POSIX interface for S_IRUSR 
#include <sys/mman.h>    // mmap
#include <errno.h>       // error number explained
#include <string.h>      // strcpy(); strerror();


/******************** PROTOTYPE ********************/
void *getArg(int argc, char *argv[]);
void *fastOpen(int i);
void *fastPrint(int i);
void *fastClose(int i);


/******************** GLOBAL ********************/ 

// MY FILE STRUCT //
struct File 
{
    char    *name;//[256];
    char    *delim;//[2];
    char    *pMem;
    int     fd;
    int     size;
    int     id;
} fSuct[2];

// FILE DESCRIPTIOR STRUCT //
struct stat st;


/******************** MAIN ********************/
int main(int argc, char *argv[])
{
    // ARGUMENTS //
    getArg(argc, argv);
    
    // ALLOCATION FUNCTIONS //
    for (int i=0; i<2; i++)
    {
        fastOpen(i);
        fastPrint(i);
        fastClose(i);
    }

    // END //
    printf("\n");
    return 0;
}


/******************** FUNCTIONS ********************/ 

//////////////////// GET ARG ////////////////////
void *getArg(int argc, char *argv[])
{
    int f = 0;
    int d = 0;

    for (int i=0; i<argc; i++)
    {
        // IDENTIFY FLAG //
        if (argv[i][0] == '-')
        {
            // GET FLAG //
            switch(argv[i][1])
            {
                // CASE SPECIFIC ACTION //
                case 'f':
                {
                    // FILE FLAG //
                    fSuct[f].name = argv[i+1];
                    stat(argv[i+1], &st);
                    fSuct[f].size = st.st_size;
                    f++;
                    break;
                }
                case 'd':
                {
                    // DELIMITER FLAG //
                    fSuct[d].delim = argv[i+1];
                    d++;
                    break;
                }
            }
        }
    }
}

//////////////////// FAST OPEN ////////////////////
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

    // DYNAMICALLY ALLOCATE //
    fSuct[i].pMem = mmap
    (
          NULL
        , fSuct[i].size
        , PROT_READ | PROT_WRITE
        , MAP_SHARED
        , fSuct[i].fd
        , 0
    );
}

//////////////////// FAST PRINT //////////////////// 
void *fastPrint(int i)
{
    // PRINT FILE //
    printf("\nPrint %s\n", fSuct[i].name);
    for (int j=0; j<fSuct[i].size; j++)
    {
        printf("%c", fSuct[i].pMem[j]);
    }                 
}

//////////////////// FAST CLOSE //////////////////// 
void *fastClose(int i)
{
    // DEALLOCATE & CLOSE //
    munmap(fSuct[i].pMem, fSuct[i].size);
    close(fSuct[i].fd);
}
