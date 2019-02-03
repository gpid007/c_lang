#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void swap(int *x, int *y);
int pivot(int i, int j);
void quicksort(int list[], int m, int n);
void display(int list[], const int n);
 
int main()
{
    int list[SIZE];
    for(int i = 0; i<SIZE; i++)
        list[i] = rand();
 
    display(list, SIZE);
    quicksort(list, 0, SIZE-1);
    display(list, SIZE);

    return 0;
}
 
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
int pivot(int i, int j)
{
    return((i + j) / 2);
}
 
void quicksort(int list[], int m, int n)
{
    int key, i, j, k;
    if (m < n)
    {
        k = pivot(m, n);
        swap(&list[m], &list[k]);
        key = list[m];
        i = m + 1;
        j = n;
        while (i<=j)
        {
            while ((i <= n) && (list[i] <= key))
                i++;
            while ((j >= m) && (list[j] > key))
                j--;
            if (i < j)
                swap(&list[i], &list[j]);
        }
        swap(&list[m], &list[j]);
        quicksort(list, m, j-1);
        quicksort(list, j+1, n);
    }
}

void display(int list[], const int n)
{
    printf("\n");
    for(int i=0; i<n; i++)
        printf("%d ",list[i]);
}
