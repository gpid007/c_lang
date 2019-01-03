#include <stdio.h>
#include <string.h>

#define CHECK(X) ({\
    int __val = (X);\
    (__val ==-1 ? ({\
        fprintf(stderr,"[ERR] "__FILE__ "%d -- %s\n", __LINE__, strerror(errno));\
        exit(-1);\
        -1;\
    }) : __val);\
})

int main()
{
    int a, c;
    char b;
    printf("\nhi");
    c = a + b;
    printf("\n%d\n", c);
    return 0;
}
