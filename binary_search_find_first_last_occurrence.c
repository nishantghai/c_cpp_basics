/*
Filename    : binary_search_find_first_last_occurrence.c
Author      : Nishant Ghai
Problem     : Find the first occurrence of a given number in a sorted array using binary search. The input sorted array may have duplicates.
              Find the first or the last occurrence of the given number.
*/

#include <stdio.h>
#include <stdlib.h>


int main()
{
    int low = 0, high=0, mid=0, result=0, arr_size=0, i=0;

    /*SORTED ARRAY*/
    int arr[] = {2,2,11,16,16,16,24,28,31,56,73,73,84,91,91,92};
    int x = 91; //data to be searched in the array
    
    arr_size = sizeof(arr)/sizeof(int);


    printf("\nThe input array is:\n");
    for( i=0;i<arr_size;i++)
    {
        printf("\narr[%d]=%d",i,arr[i]);
    }

    result = -1;
    low = 0;
    high = arr_size-1;

    while( low <= high )
    {
        mid = low + ((high-low)/2);

        if( x == arr[mid] )
        {
            result = mid; //save the index in result; 

            //but dont end the loop, continue looking for the smaller half for the first occurrence
            // and larger half for the last occurrence

            //To look for the first occurrence
            high = mid-1; //continue search for 'x' in the lower half
            
            //To look for the last occurrence
            // low = mid+1 //continue to search for 'x' in the upper half
        }
        else if( x < arr[mid] )
        {
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
    }

    if( result != -1 )
    {
        printf("\nThe first occurrence of %d in the given array is at index %d",x,result);
    }
    else
    {
        printf("\n%d is NOT found in the given array.\n",x);
    }

    printf("\n\n");
    return 0;
}
