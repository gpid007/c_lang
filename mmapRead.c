#include <sys/types.h> 
#include <fcntl.h>    // file control
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>   // fd = file descriptor
#include <sys/stat.h> // return information about a file, in the buffer pointed to by statbuf.
#include <unistd.h>   // -- " --


int main(int argc, char** argv)
{
    int fd = open("/home/greg/Downloads/big.txt", O_RDWR, S_IRUSR | S_IWUSR);
    struct stat sb;

    if (fstat(fd, &sb) == -1)
    {
        perror("\nCould not get file size");
    }
    printf("\nFile size is %ld", sb.st_size);

    char* inMemFile = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    printf("\nPrint file, as an array of characters...\n\n");
    for (int i=0; i<sb.st_size; i++)
    {
        printf("%c", inMemFile[i]);
    }
    printf("\n");

    munmap(inMemFile, sb.st_size);
    close(fd);
}
