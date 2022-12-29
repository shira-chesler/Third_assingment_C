#include <stdio.h>

void shift_element(int* arr, int i){
    for (int j = i; j > 0; j--)
    {
        *(arr+j) = *(arr+j-1);
    }
}

int find_location_in_sorted(int* arr, int start_idx, int value_to_find_place_for)
{
    while (start_idx>=0)
    {
        if (start_idx==0)
        {
            if (*(arr+start_idx)<=value_to_find_place_for)
            {
                return 1;
            }
            else
            {
                return 0;
            }
            
        }
        if (value_to_find_place_for>=*(arr+start_idx))
        {
            return start_idx+1;
        }
        start_idx--;
    }
    return -1; //a problem occured
}

void insertion_sort(int* arr, int len){
    for (int i=1; i<len; i++)
    {
        int new_value = *(arr+i);
        int location_in_sort;
        location_in_sort = find_location_in_sorted(arr, i-1, new_value);
        if (location_in_sort<0)
        {
            printf("an error that dosen't suppose to happen occured");
        }
        shift_element(arr+location_in_sort, i-location_in_sort); //i-1-location_in_sort+1=i-loction_in_sort
        *(arr+location_in_sort) = new_value;
    }
}