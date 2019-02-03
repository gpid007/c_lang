#include <stdio.h>
 
void quicksort(int *A, int len);
 
int main (void) 
{
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    int i;

    /* PRINT ARRAY */
    for (i=0; i<n; i++)
        printf("%d ", a[i]);
    printf("\n");
 
    quicksort(a, n);
 
    /* PRINT SORTED */
    for (i = 0; i < n; i++) 
        printf("%d ", a[i]);
    printf("\n");
 
    return 0;
}
 
void quicksort(int *A, int len) 
{
    int pivot, i, j, temp;
    
    if (len < 2) 
        return;
    
    pivot = A[len / 2];
    for (i=0, j=len-1; ; i++, j--)
    {
        while (A[i] < pivot) 
            i++;
        while (A[j] > pivot) 
            j--;
        if (i >= j) 
            break;
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
 
    quicksort(A, i);
    quicksort(A+i, len-i);
}

