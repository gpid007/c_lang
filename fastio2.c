#include <stdio.h>       // handling I/O
#include <ctype.h>       // int isspace(int c);
#include <stdlib.h>      // exit(-1), size_t
#include <fcntl.h>       // file control    --fd
#include <sys/stat.h>    // file descriptor --fd
#include <unistd.h>      // POSIX interface for S_IRUSR
#include <sys/mman.h>    // mmap
#include <errno.h>       // error number explained
#include <string.h>      // strcpy(); strerror();

#define N 2              // number of files
#define fWidth 4         // right align int -> max 999


/******************** PROTOTYPE ********************/
void *getArg(int argc, char *argv[]);
void *fastOpen(int i);
void *fastPrint(int i);
void *fastClose(int i);
void *fastCount(int i);
void *makeMatrix(int i);
void *printMatrix(int i, char which[5]);
void *freeMatrix(int i, char which[5]);
void *dotatrix();


/******************** GLOBAL ********************/

// FILE STRUCT //
struct File
{
    char    *name;
    char    *pMem;
    int     fd;
    int     size;
    int     col;
    int     row;
    int     **M;
} F[N];

// DOT MATRIX //
struct Matrix
{
    int     **M;
    int     row;
    int     col;
    int     max;
} dot;

// FILE DESCRIPTIOR STRUCT //
struct stat ST;


/******************** MAIN ********************/
int main(int argc, char *argv[])
{
    getArg(argc, argv);

    for (int i=0; i<N; i++)
    {
        fastOpen(i);
        fastCount(i);
        makeMatrix(i);
        fastClose(i);
        printMatrix(i, "M");
    exit(-1);
    };

    dotatrix();
    freeMatrix(0, "M");
    freeMatrix(1, "M");
    printMatrix(1, "dot");
    freeMatrix(0, "dot");

    printf("\n");
    return 0;
}


/******************** FUNCTIONS ********************/

//////////////////// GET ARG ////////////////////
void *getArg(int argc, char *argv[])
{
    for (int i=0; i<argc; i++)
    {
        F[i].name = argv[i+1];
        stat(argv[i+1], &ST);
        F[i].size = ST.st_size;
    }
}

//////////////////// FAST OPEN ////////////////////
void *fastOpen(int i)
{
    F[i].fd = open(F[i].name, O_RDWR, S_IRUSR | S_IWUSR);

    if (fstat(F[i].fd, &ST) == -1)
    {
        fprintf(stderr, "\n[ERR %i] %s", errno, strerror(errno));
        exit(-1);
    }

    F[i].pMem = mmap
    (
        NULL
        , F[i].size
        , PROT_READ | PROT_WRITE
        , MAP_SHARED
        , F[i].fd
        , 0
    );
}

//////////////////// FAST PRINT ////////////////////
void *fastPrint(int i)
{
    printf("\nPrint %s\n", F[i].name);
    for (int j=0; j<F[i].size; j++)
    {
        printf("%c", F[i].pMem[j]);
    }
}

//////////////////// FAST CLOSE ////////////////////
void *fastClose(int i)
{
    munmap(F[i].pMem, F[i].size);
    close(F[i].fd);
}

//////////////////// FAST COUNT ////////////////////
void *fastCount(int i)
{
    F[i].col = 0;
    F[i].row = 0;

    for (int x=0; x<F[i].size; x++)
    {
        if (F[i].pMem[x] == '\n')
        {
            F[i].row++;
        }
        if (isspace(F[i].pMem[x]))
        {
            F[i].col++;
        }
    }
    printf("\nrow %d col %d", F[i].row, F[i].col);
    printf("\n");
}

//////////////////// MAKE MATRIX ////////////////////
void *makeMatrix(int i)
{
    F[i].M = (int **)malloc(F[i].row * sizeof(int *));
    for (int row=0; row<F[i].row; row++)
    {
        F[i].M[row] = (int *)malloc(F[i].col * sizeof(int));
    }

    int row = 0;
    int col = 0;
    int prv;
    int nxt;
    for (int x=0; x<F[i].size; x++)
    {
        char mChar = F[i].pMem[x];
        int ctr = 0;
        if (mChar == '\n')
        {
            row++;
            col = 0;
        }
        while (!isspace(mChar) && mChar != '\n')
        {
            ctr++;
            mChar = F[i].pMem[ctr];

        }
        ctr = 0;
        F[i].M[row][col] = mChar - '0';
        col++;
    }
}

//////////////////// PRINT MATRIX ////////////////////
void *printMatrix(int i, char which[5])
{
    printf("\n");
    if (strcmp("M", which) == 0)
    {
        for (int r=0; r<F[i].row; r++)
        {
            for (int c=0; c<F[i].col; c++)
            {
                printf("%*d", fWidth, F[i].M[r][c]);
            }
            printf("\n");
        }
    }
    if (strcmp("dot", which) == 0)
    {
        for (int r=0; r<dot.row; r++)
        {
            for (int c=0; c<dot.col; c++)
            {
                printf("%*d", fWidth, dot.M[r][c]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

//////////////////// FREE MATRIX ////////////////////
void *freeMatrix(int i, char which[5])
{
    if (strcmp("M", which) == 0)
    {
        free(F[i].M);
    }
    if (strcmp("dot", which) == 0)
    {
        free(dot.M);
    }
}

//////////////////// DOT MATRIX ////////////////////
void *dotatrix()
{
    dot.row = F[0].row;
    dot.col = F[1].col;
    dot.max = 0;

    dot.M = (int **)malloc(dot.row * sizeof(int *));
    for (int row=0; row<dot.row; row++)
    {
        dot.M[row] = (int *)malloc(dot.col * sizeof(int *));
    }

    for (int row=0; row<dot.row; row++)
    {
        for (int col=0; col<dot.col; col++)
        {
            dot.M[row][col] = 0;
            for (int x=0; x<F[1].col; x++)
            {
                dot.M[row][col] += F[0].M[row][x] * F[1].M[x][col];
                // printf("%d %d %d : %d\n", row, col, x, dot.M[row][col]);
            }
            if (dot.M[row][col] > dot.max)
            {
                dot.max = dot.M[row][col];
            }
        }
    }
}

