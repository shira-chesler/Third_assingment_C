#include <stdio.h>
#include "insertionheader.h"

#define ARRAY_SIZE 50

int main()
{
    int i = 0;
    int arr[ARRAY_SIZE];
    int temp=0;
    while (i<ARRAY_SIZE)
    {
        scanf("%d", &temp);
        *(arr+i) = temp;
        i++;
    }
    int* parr = arr;
    insertion_sort(parr, ARRAY_SIZE);
    i=1;
    printf("%d",*(parr));
    while (i<ARRAY_SIZE)
    {
        printf(",%d",*(parr+i));
        i++;
    }
    printf("\n");
    return 0;
}
