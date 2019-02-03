#include <stdio.h>

// PROTOTYPE
void swap(int *a, int *b);
void quicksort(int *target, int left, int right);

// MAIN
int main() 
{
    int len;
    int arr[] = { 2, 6, 3, 8, 5, 4, 1, 9, 7, 1 };
    len = (sizeof(arr)/sizeof(int));

    quicksort(arr, 0, len);

    for(int i=0; i<len; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}

// FUNCTION
void quicksort(int *target, int left, int right) 
{
    if (left >= right) 
        return;

    int l = left;
    int r = right;
    int pivot = target[l];
    
    for(;;) 
    {
        if (l >= r) 
            break;
        while (target[l] < pivot)
            l++;
        while (pivot < target[r])
            r++;
        swap( &target[l], &target[r]);
        if (target[l] < pivot) 
            l++;
        if (pivot < target[r]) 
            r--;
    }

    quicksort(target, left, l-1);
    quicksort(target, r+1, right);
}

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
