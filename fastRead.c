#include <stdio.h>      // handling input output
#include <stdlib.h>     // size_t, wchar_t, div_t, ldiv_t
#include <fcntl.h>      // fd = open(...)
#include <sys/stat.h>   // return file descriptor struct 
#include <unistd.h>     // POSIX interface for S_IRUSR ...
#include <sys/mman.h>   // mmap
#include <errno.h>      // error number explained
#include <string.h>     // handling strings
#include <pthread.h>    // thread API


void* checkArg(int argc, char* argv[]);


int main(int argc, char* argv[])
{
    checkArg(argc, argv);
    printf("\n");
    return 0;
}


void* checkArg(int argc, char* argv[])
{
    char delim;         // Delimiter
    int fd;             // FileDesrciptor
    char* inMemFile;    // inMemoryFile
    struct stat sv;     // StatVariable

    for (int i=0; i<argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
                case 'f':
                {
                    fd = open(argv[i+1], O_RDWR, S_IRUSR | S_IWUSR); 
                 
                    if (fstat(fd, &sv) == -1)
                    {
                        fprintf(stderr, "\n[ERROR %i] %s", errno, strerror(errno));
                        exit(-1);
                    }
                    printf("\nFilesize: %ld Bytes\n", sv.st_size); 
                    
                    inMemFile = mmap(NULL, sv.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
                    for (int i=0; i<sv.st_size; i++)
                    {
                        printf("%c", inMemFile[i]);
                    }                 
                    munmap(inMemFile, sv.st_size);
                    
                    close(fd);
                    break;
                }
                case 'd':
                {
                    delim = argv[i+1][0];
                    printf("%s", &delim);
                    break;
                }
            }
        }
    }
}
