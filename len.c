#include <stdio.h>

int main()
{
    char arr[] = "Columbus";
    int answer;

    answer = sizeof(arr) / sizeof( typeof(arr[0]) ) - 1;
    printf("\n%u\n", answer);

    return 0;
}
