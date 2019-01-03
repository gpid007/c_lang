#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

int main()
{
    int myAge = 31;
    int * pAge = &myAge;

    myAge = 32;
    printf("\n%d\n", *pAge);

    int vals[5] = {1, 2, 3, 4, 5};
    printf("\na%d", vals[0]);
    printf("\nb%d", *vals);
    printf("\nc%d", *(vals+1));
      
    char myName[81];
    char *pName = myName;
    printf("\nGet Name\n");
    fgets(pName, 81, stdin);
    printf("%s", pName);

    int *pInt[50];

// l-r; r-t; u-f; d-s
    
    return 0;
}
