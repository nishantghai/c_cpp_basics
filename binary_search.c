/*
filename : binary_search.c
author : Nishant Ghai
*/

#include <stdio.h>

/*This is the recursive binary search algorithm*/
int binary_search( int arr[], int low, int high, int x )
{
    int mid = -1;

    if( low > high )
    {
        return -1;
    }

    mid = low + (( high - low )/2);

    if( arr[mid] == x )
    {
        return mid;
    }
    else if( arr[mid] < x )
    {
        return binary_search( arr, mid+1, high, x);
    }
    else
    {
        return binary_search( arr, low, mid-1, x);
    }
}


/*This is the wrapper to recursive binary search algorithm*/
int binary_search_recursive( int arr[], int arr_size, int x )
{
    return binary_search( arr, 0, arr_size-1, x );
}

/*This is the iterative binary search algorithm*/
int binary_search_iterative( int arr[], int arr_size, int x )
{
    int low = 0 , high = 0 , mid = 0;

    low = 0;
    high = arr_size-1;

    while( low <= high )
    {
        // mid = ( low + high ) / 2;

        //better calculation as low+high might cause overflow
        mid = low + ( ( high - low )/2 );

        if( arr[mid] == x )
        {
            return mid; //if match found return index at which it was found
        }
        else if( arr[mid] < x )
        {
            low = mid+1; //if mid element of array is smaller, search in the upper half
        }
        else
        {   //if mid element of array is larger, search in the lower half
            high = mid-1;
        }
    }

    return -1; //if match still not found, return -1
}

int main()
{
    int arr[] = {11,22,33,44,55,66,77,88,99} ; // !!! SORTED ARRAY!!!
    int arr_size = 0 , result = -1 , i = 0;
    int data = 99; // data to be searched in arrary

    arr_size = ( sizeof(arr) / sizeof(int) );

    printf("\nThe given sorted array is:\n");
    for( i=0; i<arr_size; i++)
    {
        printf("arr[%d]=%d\n",i,arr[i]);
    }
    
    printf("\n\nSearching for %d in given array.\n",data);
    
    //result = binary_search_iterative( arr , arr_size , data );
    result = binary_search_recursive( arr , arr_size , data );

    if( result == -1 )
    {
        printf("\nData %d does not exist in the given array.",data);
    }
    else
    {
        printf("\nData %d exist in the given array at index %d.",data,result);
    }

    printf("\n\n");
    return 0;
}

//end of file
